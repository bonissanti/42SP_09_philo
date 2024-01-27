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
	t_status	*status;

	status = philo->status;
	sem_wait(status->forks);
	print_actions(philo, "has taken a fork");
	sem_post(status->forks);
	usleep(philo->status->time_to_die * 1000);
	print_death(philo, "died");
	return ;
}

static void	*philo_routine(void *arg)
{
	t_status	*status;
	t_philo		*philo;

	philo = (t_philo *)arg;
	status = philo->status;
	if (philo->id % 2 == 0)
		usleep(5000);
	while (1)
	{
		eating(philo);
		if (philo->had_dinner == status->nbr_must_eat
			&& status->nbr_must_eat > 0)
			break ;
		sleeping(philo);
		thinking(philo);
	}
	clean_up(status);
	exit(0);
}

static void	check_child_status(t_philo *philo, t_status *status)
{
	int			i;
	int			proc_status;
	long int	time_now;

	i = -1;
	proc_status = 0;
	while (++i < status->nbr_philo)
	{
		waitpid(status->pid[i], &proc_status, 0);
		proc_status = WEXITSTATUS(proc_status);
		if (proc_status == 0 || proc_status == 1)
		{
			if (proc_status == 1)
			{
				time_now = get_time_now() - status->start;
				printf("%ld %d %s\n", time_now, philo[i].id, "died");
			}
			i = -1;
			while (++i < status->nbr_philo)
				kill(status->pid[i], SIGKILL);
		}
		break ;
	}
}

void	start_semaphores(t_philo *philos, t_status *status)
{
	int			i;

	i = -1;
	while (++i < status->nbr_philo)
	{
		status->pid[i] = fork();
		if (status->pid[i] == 0)
		{
			philo_routine(&philos[i]);
			exit(0);
		}
	}
	check_child_status(philos, status);
}

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
