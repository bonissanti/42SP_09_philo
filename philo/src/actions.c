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

void	eating(t_philo *philo)
{
	t_status *status;

	status = philo->status;
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

void	thinking(t_philo *philo)
{
	print_actions(philo, "is thinking");
	usleep(500);
}

void	sleeping(t_philo *philo)
{
	print_actions(philo, "is sleeping");
	usleep(philo->status->time_to_sleep * 1000);
}