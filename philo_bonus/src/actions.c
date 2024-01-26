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

#include "../include/philo_bonus.h"

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
	t_status	*status;

	status = philo->status;
	sem_wait(status->forks);
	sem_wait(status->forks);
	print_actions(philo, "has taken a fork");
	print_actions(philo, "has taken a fork");
}

static	void	put_forks(t_philo *philo)
{
	t_status	*status;

	status = philo->status;
	sem_post(status->forks);
	sem_post(status->forks);
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
	long int	current_time;

	status = philo->status;
	get_forks(philo);
	print_actions(philo, "is eating");
	philo->time_last_eat = get_time_now() - status->start;
	usleep(status->time_to_eat * 10);
	philo->had_dinner++;
	put_forks(philo);

	// checagem de morte por tempo
	current_time = get_time_now() - status->start;
	if (current_time - philo->time_last_eat > status->time_to_die)
	{
		printf("current_time: %ld\n", current_time);
		exit(1);

	}
	if (philo->had_dinner == status->nbr_eat)
		exit(0);
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
	long int	current_time;

	status = philo[0].status;

	// checagem de morte por tempo

	print_actions(philo, "is thinking");
	usleep(500);
	current_time = get_time_now() - status->start;
	if (current_time - philo->time_last_eat > status->time_to_die)
		exit(1);
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
	long int	current_time;

	status = philo[0].status;

	print_actions(philo, "is sleeping");
	usleep(philo->status->time_to_sleep * 1000);
	
	// checagem de morte por tempo
	current_time = get_time_now() - status->start;
	if (current_time - philo->time_last_eat > status->time_to_die)
		exit(1);
}
