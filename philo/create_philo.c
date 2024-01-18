#include "./philo.h"

		// if (get_time() - current->last_eat_time > current->time_to_die)
		// {
		// 	print_time(status);
		// 	printf(" %d died\n", current->id);
		// 	status->running = false;
		// 	pthread_mutex_unlock(&current->left_fork);
		// 	break ;
		// }

		// //eating
		// print_time(status);

		// printf(" %d is eating\n", current->id);
		// current->last_eat_time = get_time();
		// usleep(current->time_to_eat * 1000);
		// pthread_mutex_unlock(&current->left_fork);
		// pthread_mutex_unlock(&current->right_fork);

		// //sleeping
		// print_time(status);
		// printf(" %d is sleeping\n", current->id);
		// usleep(current->time_to_sleep * 1000);

static void	*philo_behavior(void *philo)
{
	t_philos	*current;
	t_status	*status;

	status = get_status();
	current = (t_philos *)philo;
	while (status->running)
	{
		thinking(status, current);
		if (get_time() - current->last_eat_time > current->time_to_die)
		{
			print_time(status);
			if (status->died == false)
			{
				printf(" %d died\n", current->id);
				status->died = true;
			}
			status->running = false;
			break ;
		}
	}
	return (NULL);
}

// void	*monitoring(void *ptr)
// {
// 	t_status 	*status;
// 	t_philos 	*philos;

// 	(void)ptr;
// 	status = get_status();
// 	philos = status->head;
// 	while (status->running)
// 	{
// 		if (get_time() - philos->last_eat_time > philos->time_to_die)
// 		{
// 			pthread_mutex_lock(&philos->print);
// 			print_time(status);
// 			printf(" %d died\n", philos->id);
// 			status->running = false;
// 			pthread_mutex_unlock(&philos->print);
// 			break ;
// 		}
// 		philos = philos->next;
// 	}
// 	return (NULL);
// }




int	handle_philo(t_status *status, t_philos *philo)
{
	int i;
	t_philos *current;
	pthread_t *thread;

	i = -1;
	current = philo;
	thread = (pthread_t *)malloc(sizeof(pthread_t) * status->num_philos + 1);
	while (++i < status->num_philos)
	{
		pthread_create(thread + i, NULL, &philo_behavior, (void *)current);
		current = current->next;
	}
	i = -1;
	current = philo;
	while (++i < status->num_philos)
	{
		pthread_join(thread[i], NULL);
		if (status->running == false)
			break ;
		current = current->next;
	}
	free(thread);
	return (0);
}