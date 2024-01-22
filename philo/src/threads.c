#include "../include/philo.h"

int		teste = 0;
// pthread_mutex_t mutex;

static void	*philo_routine(void *arg)
{
	int			i;
	t_philo		*philo;
	t_status	*status;

	i = -1;
	philo = (t_philo *)arg;
	status = philo->status;
	while (++i < philo->status->nbr_philo)
	{
		pthread_mutex_lock(&status->print);
		teste += 10;
		// printf("teste: %d\n", teste);
		pthread_mutex_unlock(&status->print);
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	int			i;
	t_status	*status;
	
	i = -1;
	status = (t_status *)arg;
	while (1)
	{
		while (++i < status->nbr_philo)
		{
			pthread_mutex_lock(&status->print);
			// printf("teste: %d\n", teste);
			pthread_mutex_unlock(&status->print);
		}
		ulseep(10000);
	}
}

void	start_threads(t_philo *philos, t_status *status)
{
	int 		i;
	pthread_t	*threads;

	i = -1;
	// pthread_mutex_init(&mutex, NULL);
	threads = ft_calloc(status->nbr_philo, sizeof(pthread_t));
	if (!threads)
		return ;
	
	while (++i < status->nbr_philo)
	{
		if (pthread_create(&threads[i], NULL, &philo_routine, (void *)&philos[i]))
			printf("Error: thread creation failed\n");
	}
	// pthread create do monitoramento a ser adicionado
	i = -1;
	while (++i < status->nbr_philo)
	{
		if (pthread_join(threads[i], NULL))
			printf("Error: thread join failed\n");
	}
	// pthread join do monitoramento a ser adicionado
	// pthread_mutex_destroy(&mutex);
	printf("teste: %d\n", teste);
	free(threads);
}
