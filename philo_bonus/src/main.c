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

#include "../include/philo_bonus.h"

void	clean_up(t_status *status)
{
	sem_close(status->print);
	sem_close(status->eat);
	sem_close(status->dead);
	sem_close(status->nbr_eat);
	sem_close(status->forks);
	free(status->pid);
	free(status);
}

/**
 * Function: main
 * -----------------
 * Every important function pass through here. At first, we check if the
 * arguments are valid, then we initialize the status of the simulation and
 * the philosophers. Finally, we check if the number of philosophers is 1,
 * and if it is, we call the one_philo function, otherwise we call the
 * start_semaphores function, because exists two different ways to run the
 * simulation. Then, after the simulation is over (or the number of
 * philosophers is 0), we free the memory allocated for the status and the
 * philosophers.
 *  
 * @param: argc: The number of arguments.
 * @param: **argv: The arguments that are going to be checked.
 * @var: *status: The status of the simulation.
 * @var: *philo: The philosophers.
 * 
 * @return: Returns 0 if the simulation is successful, 1 otherwise.
 *
 */

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
		start_semaphores(philo, status);
	// else
	// 	printf("Error: Number of philosophers must be greater than 0\n");
	clean_up(status);
	free(philo);
	return (0);
}
