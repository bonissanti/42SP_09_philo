/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:47:56 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/23 18:58:30 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	one_philo(t_philo *philo)
{
	sem_wait(philo->forks);
	print_actions(philo, "has taken a fork");
	sem_post(philo->forks);
	usleep(philo->status->time_to_die * 1000);
	print_death(philo, "died");
	return ;
}

static void	*philo_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(8000);
	while (1)
	{
		eating(philo);
		thinking(philo);
		sleeping(philo);
	}
	return (NULL);
}

void	start_semaphores(t_philo *philos, t_status *status)
{
	int			i;
	int			proc_status;

	i = -1;
	proc_status = 0;
	while (++i < status->nbr_philo)
	{
		status->pid[i] = fork();
		if (status->pid[i] == 0)
		{
			philo_routine(&philos[i]);
			exit(0);
		}
	}
	i = -1;
	while (++i < status->nbr_philo)
	{
		waitpid(status->pid[i], &proc_status, 0);
		if (WEXITSTATUS(proc_status) == 1)
		{
			long int death_time = get_time_now() - status->start;
			printf("%ld %d died\n", death_time, philos[i].id);
			i = -1;
			while (++i < status->nbr_philo)
				kill(status->pid[i], SIGKILL);
		}
		if (WEXITSTATUS(proc_status) == 0)
		{
			status->nbr_philo--;
			i = -1;
			while (++i < status->nbr_philo)
				kill(status->pid[i], SIGKILL);
		}
		break;
		
	}
}

