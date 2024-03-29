/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:47:40 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/23 18:13:12 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * Function: Init_status
 * -----------------
 * This function is used to initialize the status of the simulation. Here we
 * call the atosz function to convert the arguments from string to size_t,
 * then we initialize the mutexes and the forks, according to the number of
 * philosophers.
 *  
 * @param: argc: The number of arguments.
 * @param: **argv: The arguments that are going to be checked.
 * @param: *status: The status of the simulation.
 * @var: i: The iterator.
 * @fn: pthread_mutex_init: Initializes the mutex.
 * 
 * @return: Returns nothing.
 *
 */

void	init_status(int argc, char **argv, t_status *status)
{
	int	i;

	i = -1;
	status->nbr_philo = (int)atosz(argv[1]);
	status->time_to_die = (int)atosz(argv[2]);
	status->time_to_eat = (int)atosz(argv[3]);
	status->time_to_sleep = (int)atosz(argv[4]);
	if (argc == 6)
		status->nbr_must_eat = (int)atosz(argv[5]);
	else
		status->nbr_must_eat = -1;
	status->had_dined = 0;
	status->is_dead = 0;
	status->out_of_food = 0;
	status->start = get_time_now();
	pthread_mutex_init(&status->print, NULL);
	pthread_mutex_init(&status->eat, NULL);
	pthread_mutex_init(&status->dead, NULL);
	pthread_mutex_init(&status->nbr_eat, NULL);
	status->forks = malloc(sizeof(pthread_mutex_t) * status->nbr_philo);
	while (++i < status->nbr_philo)
		pthread_mutex_init(&status->forks[i], NULL);
}

/**
 * Function: Init_philos
 * -----------------
 * This function is used to initialize the philosophers. Basically, we
 * initialize the id, the number of times that the philosopher has eaten,
 * the time of the last meal, the status of the simulation, the forks and
 * the right and left forks.
 *  
 * @param: *status: The status of the simulation.
 * @var: i: The iterator.
 * 
 * @return: Returns nothing.
 *
 */

void	init_philos(t_philo *philo, t_status *status)
{
	int	i;

	i = -1;
	while (++i < status->nbr_philo)
	{
		philo[i].id = i + 1;
		philo[i].had_dinner = 0;
		philo[i].time_last_eat = 0;
		philo[i].status = status;
		philo[i].left_fork = &status->forks[i];
		philo[i].right_fork = &status->forks[(i + 1) % status->nbr_philo];
	}
}
