/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:47:56 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/23 15:17:07 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	*philo_routine(void *arg)
{
	t_philo		*philo;
	t_status	*status;

	philo = (t_philo *)arg;
	status = philo->status;
	while (1)
	{
		pthread_mutex_lock(&status->print);
		if (status->is_dead == 1)
		{
			pthread_mutex_unlock(&status->print);
			break ;
		}
		pthread_mutex_unlock(&status->print);
		eating(philo);
		thinking(philo);
		sleeping(philo);
		// printf("philo->had_dinner = %d\n", philo->had_dinner);
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	int			i;
	long int	time_now;
	t_philo		*philo;
	t_status	*status;

	philo = (t_philo *)arg;
	status = philo[0].status;
	while (1)
	{
		i = -1;
		while (++i < status->nbr_philo)
		{
			pthread_mutex_lock(&status->print);
			time_now = get_time_now();
			if (time_now - philo[i].time_last_eat > status->time_to_die)
			{
				status->is_dead = 1;
				pthread_mutex_unlock(&status->print);
				return (NULL);
			}
			// if (philo_dined(philo) && status->nbr_must_eat > 0)
			// {
			// 	status->is_dead = 1;
			// 	pthread_mutex_unlock(&status->print);
			// 	return (NULL);
			// }
			pthread_mutex_unlock(&status->print);
		}
		usleep(1000);
	}
	return (NULL);
}

// void	*monitor(void *arg)
// {
// 	int			i;
// 	t_bool		all_ate_enough;
// 	long int	time_now;
// 	t_philo		*philo;
// 	t_status	*status;
	
// 	philo = (t_philo *)arg;
// 	status = philo[0].status;
// 	while (1)
// 	{
// 		i = -1;
// 		all_ate_enough = true;
// 		while (++i < status->nbr_philo)
// 		{
// 			pthread_mutex_lock(&status->print);
// 			time_now = get_time_now();
// 			if (time_now - philo[i].time_last_eat > status->time_to_die)
// 			{
// 				status->is_dead = 1;
// 				pthread_mutex_unlock(&status->print);
// 				return (NULL);
// 			}
// 			if (status->nbr_must_eat > 0 && philo[i].times_ate < status->nbr_must_eat)
// 				all_ate_enough = false;
// 			pthread_mutex_unlock(&status->print);
// 		}
// 		if (all_ate_enough && status->nbr_must_eat > 0)
// 		{
// 			status->is_dead = 1;
// 			break ;
// 		}
// 		usleep(1000);
// 	}
// 	return (NULL);
// }

// backup 1
// void	*monitor(void *arg)
// {
// 	t_philo		*philo;
// 	t_status	*status;
	
// 	philo = (t_philo *)arg;
// 	status = philo[0].status;
// 	while (1)
// 	{
// 		pthread_mutex_lock(&status->print);
// 		if (teste >= 20)
// 		{
// 			status->is_dead = 1;
// 			pthread_mutex_unlock(&status->print);
// 			break ;
// 		}
// 		// if (status->is_dead == 1)
// 		// {
// 		// 	pthread_mutex_unlock(&status->print);
// 		// 	return (NULL);
// 		// }
// 		// if (status->nbr_must_eat <= 0)
// 		// {
// 		// 	pthread_mutex_unlock(&status->print);
// 		// 	break ;
// 		// }
// 		pthread_mutex_unlock(&status->print);
// 		usleep(10000);
// 	}
// 	return (NULL);
// }

void	start_threads(t_philo *philos, t_status *status)
{
	int 		i;
	pthread_t	*threads;
	pthread_t	monitoring;

	i = -1;
	threads = ft_calloc(status->nbr_philo, sizeof(pthread_t));
	if (!threads)
		return ;
	
	while (++i < status->nbr_philo)
	{
		if (pthread_create(&threads[i], NULL, &philo_routine, (void *)&philos[i]) != 0)
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
	// printf("teste: %d\n", teste);
	free(threads);
}
