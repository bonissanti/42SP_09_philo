/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:47:44 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/23 18:11:17 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_philo		*philo;
	t_status	*status;

	if (!check_args(argc, argv + 1))
		return (1);
	status = malloc(sizeof(t_status));
	init_status(argc, argv, status);
	philo = malloc(sizeof(t_philo) * status->nbr_philo);
	init_philos(philo, status);
	if (status->nbr_philo == 1)
		one_philo(philo);
	else if (status->nbr_philo > 1)
		start_threads(philo, status);
	else
		printf("Error: Number of philosophers must be greater than 0\n");
	free_status(status);
	free(philo);
	return (0);
}
