#include "../include/philo.h"

void	start_threads(t_philo *philos, t_status *status)
{
	int 		i;
	pthread_t	*threads;

	i = -1;
	threads = ft_calloc(status->nbr_philo, sizeof(pthread_t));
	if (!threads)
		return ;
	
	while (++i < status->nbr_philo)
	{
		if (pthread_create(&threads[i], NULL, &philo_routine, &philos[i]))
			printf("Error: thread creation failed\n");
	}
}
