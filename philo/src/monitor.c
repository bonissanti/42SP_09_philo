/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:04:01 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/23 17:04:57 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	end_looping(t_status *status, int type)
{
	pthread_mutex_lock(&status->dead);
	if (type == 0)
		status->is_dead = 1;
	else
		status->out_of_food = 1;
	pthread_mutex_unlock(&status->dead);
}

static int	check_death_time(t_philo *philo, t_status *status)
{
	int			i;
	long int	time_now;

	i = -1;
	while (++i < status->nbr_philo)
	{
		pthread_mutex_lock(&status->print);
		pthread_mutex_lock(&status->dead);
		time_now = get_time_now() - status->start;
		if (time_now - philo->time_last_eat > status->time_to_die)
		{
			pthread_mutex_unlock(&status->print);
			pthread_mutex_unlock(&status->dead);
			return (1);
		}
		pthread_mutex_unlock(&status->print);
		pthread_mutex_unlock(&status->dead);
	}
	return (0);
}

static int	all_ate_enough(t_philo *philo, t_status *status)
{
	int	i;
	int	all_ate_enough;

	i = -1;
	all_ate_enough = (status->nbr_must_eat > 0);
	while (++i < status->nbr_philo)
	{
		pthread_mutex_lock(&status->nbr_eat);
		if (all_ate_enough && philo[i].had_dinner < status->nbr_must_eat)
			all_ate_enough = 0;
		pthread_mutex_unlock(&status->nbr_eat);
	}
	return (all_ate_enough);
}

void	*monitor(void *arg)
{
	t_philo		*philo;
	t_status	*status;

	philo = (t_philo *)arg;
	status = philo[0].status;
	while (1)
	{
		if (check_death_time(philo, status))
		{
			end_looping(status, 0);
			print_death(philo, "died");
			return (NULL);
		}
		pthread_mutex_lock(&status->print);
		if (all_ate_enough(philo, status))
		{
			end_looping(status, 1);
			pthread_mutex_unlock(&status->print);
			break ;
		}
		pthread_mutex_unlock(&status->print);
		usleep(200);
	}
	return (NULL);
}
