/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:50:38 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/19 18:00:13 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	*monitoring(void *ptr)
{
	t_status 	*status;
	t_philos 	*philos;

	(void)ptr;
	status = get_status();
	philos = status->head;
	while (status->running)
	{
		while (philos)
		{
			if (get_time() - philos->last_eat_time > philos->time_to_die)
			{
				status->running = false;
				status->died = true;
			}
		}
		philos = philos->next;
	}
	return (NULL);
}
