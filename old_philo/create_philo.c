#include "./philo.h"

static void	*philo_behavior(void *philo)
{
	t_philos	*current;
	t_status	*status;

	status = get_status();
	current = (t_philos *)philo;
	while (get_status()->running)
	{
		eating(status, current);
		if (!status->running)
			break ;
		// if (get_time() - current->last_eat_time > current->time_to_die)
		// {
		// 	if (status->died == false)
		// 	{
		// 		long int time = get_time() - status->start_time;
		// 		// pthread_mutex_lock(&current->print);
		// 		printf("%ld %d %s", time, current->id, "is dead\n");
		// 		// pthread_mutex_unlock(&current->print);
		// 		status->died = true;
		// 	}
		// 	status->running = false;
		// 	pthread_mutex_unlock(&current->mutex);
		// 	break ;
		// }
		// pthread_mutex_unlock(&current->mutex);
		thinking(status, current);
	}
	return (NULL);
}




int	handle_philo(t_status *status, t_philos *philo)
{
	int i;
	t_philos *current;
	pthread_t *thread;

	i = -1;
	current = philo;
	thread = (pthread_t *)malloc(sizeof(pthread_t) * status->num_philos + 1);
	if  (!thread)
		return (1);
	while (++i < status->num_philos && status->running)
	{
		pthread_create(thread + i, NULL, &philo_behavior, (void *)current);
		pthread_mutex_lock(&current->mutex);
		if (get_status()->running == false)
		{
			pthread_mutex_unlock(&current->mutex);
			break ;
		}
		pthread_mutex_unlock(&current->mutex);
		current = current->next;
	}
	pthread_create(thread + i, NULL, &monitoring, NULL);
	i = -1;
	while (++i < status->num_philos + 1)
		pthread_join(thread[i], NULL);
	free(thread);
	return (0);
}