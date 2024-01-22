#include "../include/philo.h"

int		teste = 0;

static void	*philo_routine(void *arg)
{
	t_philo		*philo;
	t_status	*status;

	philo = (t_philo *)arg;
	status = philo->status;
	while (1)
	{
		pthread_mutex_lock(&status->print);
		if (status->is_dead == 1)
		{
			pthread_mutex_unlock(&status->print);
			break ;
		}
		teste++;
		pthread_mutex_unlock(&status->print);
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	t_philo		*philo;
	t_status	*status;
	
	philo = (t_philo *)arg;
	status = philo[0].status;
	while (1)
	{
		pthread_mutex_lock(&status->print);
		if (teste >= 20)
		{
			status->is_dead = 1;
			pthread_mutex_unlock(&status->print);
			break ;
		}
		// if (status->is_dead == 1)
		// {
		// 	pthread_mutex_unlock(&status->print);
		// 	return (NULL);
		// }
		// if (status->nbr_must_eat <= 0)
		// {
		// 	pthread_mutex_unlock(&status->print);
		// 	break ;
		// }
		pthread_mutex_unlock(&status->print);
		usleep(10000);
	}
	return (NULL);
}

void	start_threads(t_philo *philos, t_status *status)
{
	int 		i;
	pthread_t	*threads;
	pthread_t	monitoring;

	i = -1;
	threads = ft_calloc(status->nbr_philo, sizeof(pthread_t));
	if (!threads)
		return ;
	
	while (++i < status->nbr_philo)
	{
		if (pthread_create(&threads[i], NULL, &philo_routine, (void *)&philos[i]) != 0)
			printf("Error: thread creation failed\n");
	}
	if (pthread_create(&monitoring, NULL, &monitor, philos) != 0)
		printf("Error: thread creation failed\n");

	i = -1;
	while (++i < status->nbr_philo)
	{
		if (pthread_join(threads[i], NULL) != 0)
			printf("Error: thread join failed\n");
	}
	pthread_join(monitoring, NULL);
	printf("teste: %d\n", teste);
	free(threads);
}
