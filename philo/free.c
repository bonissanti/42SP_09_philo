/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:16:32 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/19 16:17:26 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_philos *philo)
{
	t_philos	*current;

	current = philo;
	while (current != philo)
	{
		pthread_mutex_destroy(&current->mutex);
		pthread_mutex_destroy(&current->print);
		pthread_mutex_destroy(&current->left_fork);
		pthread_mutex_destroy(&current->right_fork);
		current = current->next;
	}
}