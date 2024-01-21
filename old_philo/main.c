#include "./philo.h"

int main(int argc, char **argv)
{
	t_philos *philo;
	t_status *status;

	if (argc != 5)
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	status = get_status();
	status->running = true;
	status->num_philos = atoi(argv[1]);
	status->time_to_die = atoi(argv[2]);
	status->time_to_eat = atoi(argv[3]);
	status->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		status->num_meals = atoi(argv[5]);
	else
		status->num_meals = -1;
	status->start_time = get_time();
	philo = init_philo(status);
	handle_philo(status, philo);
	// monitoring(status);
	destroy_mutexes(philo);
	return (0);	
}