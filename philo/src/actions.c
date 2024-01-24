/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:47:32 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/23 18:36:27 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * Function: Get forks
 * -----------------
 * This function is used to get the forks of the philosopher. It is used
 * in the eating function. Here we check if the philosopher is even or odd
 * to avoid deadlocks, then we lock the mutexes of the forks according to
 * the philosopher's id.
 *  
 * @param: *philo: The philosopher that is going to perform the action.
 * 
 * @return: Returns nothing.
 *
 */

static	void	get_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_actions(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_actions(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_actions(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_actions(philo, "has taken a fork");
	}
}

/**
 * Function: Eating
 * -----------------
 * This function is used to make the philosopher eat. Here we call the
 * get_forks function to get the forks, then we print the action of eating
 * and finally we unlock the mutexes of the forks.
 * 
 * Besides, we have two variables that constantly change: time_last_eat and
 * had_dinner. The first one is used to check if the philosopher is dead
 * of starvation, and the second one is used to check if the philosopher 
 * has eaten the number of times that was passed as an argument. For each
 * check, we need to use mutex lock to avoid data race.
 * 
 * @param: *philo: The philosopher that is going to perform the action.
 * @var: *status: The status of the simulation.
 * 
 * @return: Returns nothing.
 *
 */

void	eating(t_philo *philo)
{
	t_status	*status;

	status = philo->status;
	get_forks(philo);
	print_actions(philo, "is eating");
	pthread_mutex_lock(&status->dead);
	philo->time_last_eat = get_time_now() - status->start;
	pthread_mutex_unlock(&status->dead);
	usleep(philo->status->time_to_eat * 1000);
	pthread_mutex_lock(&status->nbr_eat);
	philo->had_dinner++;
	pthread_mutex_unlock(&status->nbr_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

/**
 * Function: Thinking
 * -----------------
 * This function is used to make the philosopher think. Here we print the
 * action of thinking and then we make the thread sleep for 500 microseconds.
 * 
 * For avoid to print the action of thinking if the philosopher is dead, we
 * check the status of the simulation. If the philosopher is dead, we return
 * from the function.
 * 
 * @param: *philo: The philosopher that is going to perform the action.
 * @var: *status: The status of the simulation.
 * 
 * @return: Returns nothing.
 *
 */

void	thinking(t_philo *philo)
{
	t_status	*status;

	status = philo[0].status;
	pthread_mutex_lock(&status->dead);
	if (status->is_dead == 1)
	{
		pthread_mutex_unlock(&status->dead);
		return ;
	}
	pthread_mutex_unlock(&status->dead);
	print_actions(philo, "is thinking");
	usleep(500);
}

/**
 * Function: Sleeping
 * -----------------
 * This function is used to make the philosopher sleep. Here we print the
 * action of sleeping and then we make the thread sleep for the time that
 * was passed as an argument * 1000.
 * 
 * For avoid to print the action of thinking if the philosopher is dead, we
 * check the status of the simulation. If the philosopher is dead, we return
 * from the function.
 * 
 * @param: *philo: The philosopher that is going to perform the action.
 * @var: *status: The status of the simulation.
 * 
 * @return: Returns nothing.
 *
 */

void	sleeping(t_philo *philo)
{
	t_status	*status;

	status = philo[0].status;
	pthread_mutex_lock(&status->dead);
	if (status->is_dead == 1)
	{
		pthread_mutex_unlock(&status->dead);
		return ;
	}
	pthread_mutex_unlock(&status->dead);
	print_actions(philo, "is sleeping");
	usleep(philo->status->time_to_sleep * 1000);
}
