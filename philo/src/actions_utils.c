/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:25:50 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/23 18:00:13 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_bool	philo_dined(t_philo *philo)
{
	int			i;
	t_status 	*status;
	
	i = -1;
	status = philo->status;
	while (++i < status->nbr_philo)
	{
		// pthread_mutex_lock(&status->print);
		if (philo[i].had_dinner == 1)
			status->jantou++;
		// printf("nbr_dined: %d\n", status->jantou);
		if (status->jantou == status->nbr_philo)
		{
			// pthread_mutex_unlock(&status->print);
			return (true);
		}
		// pthread_mutex_unlock(&status->print);
	}
	return (false);
}

void	print_actions(t_philo *philo, char *msg)
{
	t_status *status;
	long int time_now;

	status = philo->status;
	pthread_mutex_lock(&status->print);
	if (status->is_dead == 1)
	{
		pthread_mutex_unlock(&status->print);
		return ;
	}
	time_now = get_time_now() - status->start;
	printf("%ld %d %s\n", time_now, philo->id, msg);
	pthread_mutex_unlock(&status->print);
}

void	print_death(t_philo *philo, char *msg)
{
	int			i;
	long int time_now;

	i = -1;
	time_now = get_time_now() - philo->status->start;
	printf("%ld %d %s\n", time_now, philo->id, msg);
	while (++i < philo->status->nbr_philo)
		philo->status->is_dead = 1;
}