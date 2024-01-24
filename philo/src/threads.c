/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:47:56 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/23 18:58:30 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_actions(philo, "has taken a fork");
	pthread_mutex_unlock(philo->right_fork);
	usleep(philo->status->time_to_die * 1000);
	print_death(philo, "died");
	return ;
}

static void	*philo_routine(void *arg)
{
	t_philo		*philo;
	t_status	*status;

	philo = (t_philo *)arg;
	status = philo->status;
	if (philo->id % 2 == 0)
		usleep(5000);
	while (1)
	{
		eating(philo);
		pthread_mutex_lock(&status->dead);
		if (status->is_dead == 1 || status->out_of_food == 1)
		{
			pthread_mutex_unlock(&status->dead);
			break ;
		}
		pthread_mutex_unlock(&status->dead);
		thinking(philo);
		sleeping(philo);
	}
	return (NULL);
}

void	start_threads(t_philo *philos, t_status *status)
{
	int			i;
	pthread_t	*threads;
	pthread_t	monitoring;

	i = -1;
	threads = ft_calloc(status->nbr_philo, sizeof(pthread_t));
	if (!threads)
		return ;
	while (++i < status->nbr_philo)
	{
		if (pthread_create(&threads[i], NULL, &philo_routine,
				(void *)&philos[i]) != 0)
			printf("Error: thread creation failed\n");
	}
	if (pthread_create(&monitoring, NULL, &monitor, philos) != 0)
		printf("Error: thread creation failed\n");
	i = -1;
	while (++i < status->nbr_philo)
	{
		if (pthread_join(threads[i], NULL) != 0)
			printf("Error: thread join failed\n");
	}
	pthread_join(monitoring, NULL);
	free(threads);
}

void	free_status(t_status *status)
{
	int	i;

	i = -1;
	while (++i < status->nbr_philo)
		pthread_mutex_destroy(&status->forks[i]);
	pthread_mutex_destroy(&status->print);
	pthread_mutex_destroy(&status->eat);
	pthread_mutex_destroy(&status->dead);
	pthread_mutex_destroy(&status->nbr_eat);
	free(status->forks);
	free(status);
}
