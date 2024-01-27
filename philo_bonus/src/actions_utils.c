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

#include "../include/philo_bonus.h"

/**
 * Function: Print actions
 * -----------------
 * This function is a generic function to print the actions of the
 * philosophers, like eating, sleeping, thinking or dying.
 *  
 * @param: *philo: The philosopher that is going to perform the action.
 * @param: *msg: The message to be printed.
 * 
 * @var: *status: The status of the simulation.
 * @var: time_now: The time now.
 * 
 * @return: Returns nothing.
 *
 */

void	print_actions(t_philo *philo, char *msg)
{
	t_status	*status;
	long int	time_now;

	status = philo->status;
	sem_wait(status->print);
	time_now = get_time_now() - status->start;
	printf("%ld %d %s\n", time_now, philo->id, msg);
	sem_post(status->print);
}

/**
 * Function: Print death
 * -----------------
 * This function is similar to print_actions, but it is only used to print
 * the death of a philosopher. Here we don't need to check if the philosopher
 * is dead, because this function is only called when the philosopher is dead.
 * 
 * Besides, if we had used print_actions, mandatorily we would have to call
 * pthread_mutex_lock(&status->dead) together with 
 * pthread_mutex_lock(&status->print) to check correctly if the philosopher 
 * is dead. Since we are only printing the death, this is unnecessary.
 *  
 * @param: *philo: The philosopher that is going to perform the action.
 * @param: *msg: The message to be printed.
 * 
 * @var: *status: The status of the simulation.
 * @var: time_now: The time now.
 * 
 * @return: Returns nothing.
 *
 */

void	print_death(t_philo *philo, char *msg)
{
	long int	time_now;

	sem_wait(philo->status->print);
	time_now = get_time_now() - philo->status->start;
	printf("%ld %d %s\n", time_now, philo->id, msg);
	sem_post(philo->status->print);
}
