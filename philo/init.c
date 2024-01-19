#include "./philo.h"

t_status	*get_status(void)
{
	static t_status status;

	return (&status);
}

t_philos	*add_philo(t_status *status)
{
	t_philos	*new_philo;

	new_philo = (t_philos *)malloc(sizeof(t_philos));
	if (!new_philo)
		return (NULL);
	new_philo->id = status->id;
	new_philo->time_to_die = status->time_to_die;
	new_philo->time_to_eat = status->time_to_eat;
	new_philo->time_to_sleep = status->time_to_sleep;
	new_philo->last_eat_time = status->start_time;
	pthread_mutex_init(&new_philo->mutex, NULL);
	pthread_mutex_init(&new_philo->print, NULL);
	pthread_mutex_init(&new_philo->left_fork, NULL);
	pthread_mutex_init(&new_philo->right_fork, NULL);
	new_philo->next = NULL;
	return (new_philo);
}

t_philos	*init_philo(t_status *status)
{
	t_philos	*first;
	t_philos	*last;
	int			i;

	i = -1;
	first = NULL;
	last = NULL;
	while (++i < status->num_philos)
	{
		status->id = i;
		if (i == 0)
		{
			first = add_philo(status);
			last = first;
		}
		else
		{
			last->next = add_philo(status);
			last = last->next;
		}
	}
	if (last)
		last->next = first;
	return (first);
}
