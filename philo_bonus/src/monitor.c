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

#include "../include/philo_bonus.h"

/**
 * Function: End looping
 * -----------------
 * This function is used to end the simulation. This is called when a 
 * philosopher dies or when all the philosophers ate enough. Basically, 
 * according to the type, we set the status of the simulation to dead or 
 * out of food to 1, stopping the simulation.
 *  
 * @param: *status: The status of the simulation.
 * @param: type: The type of the status that is going to be set.
 * 
 * @return: Returns the converted string.
 *
 */

static void	end_looping(t_status *status, int type)
{
	pthread_mutex_lock(&status->dead);
	if (type == 0)
		status->is_dead = 1;
	else
		status->out_of_food = 1;
	pthread_mutex_unlock(&status->dead);
}

/**
 * Function: Check death time
 * -----------------
 * This function is used to check if a philosopher is dead of starvation.
 * Basically, we check if the time now - the time of the last meal is
 * greater than the time to die. If it is, we return 1, otherwise we return
 * 0.
 * 
 * Besides, we have two mutexes, one for the print and one for the dead,
 * when we are checking the time of the last meal, we need to lock the
 * print and dead, to avoid data race.
 *  
 * @param: *philo: The philosopher that is going to perform the action.
 * @param: *status: The status of the simulation.
 * @var: i: The iterator.
 * @var: time_now: The time now.
 * @fn: pthread_mutex_lock: Locks the mutex.
 * @fn: pthread_mutex_unlock: Unlocks the mutex.
 * 
 * @return: Returns the converted string.
 *
 */

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

/**
 * Function: All ate enough
 * -----------------
 * This function is used to check if all the philosophers ate enough. Basically,
 * we check if the number of times that the philosopher has eaten is greater
 * than the number of times that was passed as an argument. If it is, we
 * return 1, otherwise we return 0.
 *  
 * @param: *philo: The philosopher that is going to perform the action.
 * @param: *status: The status of the simulation.
 * @var: i: The iterator.
 * @var: all_ate_enough: The variable that is going to be returned.
 * 
 * @return: Returns an integer
 *
 */

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
