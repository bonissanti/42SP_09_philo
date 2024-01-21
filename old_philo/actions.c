#include "./philo.h"

long int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

// void	print_time(t_status *status)
// {
// 	printf("%ld", get_time() - status->start_time);
// }


void	thinking(t_status *status, t_philos *current)
{
	pthread_mutex_lock(&current->print);
	printf("%ld %d %s", get_time() - status->start_time, current->id, "is thinking\n");
	pthread_mutex_unlock(&current->print);
	usleep(current->time_to_sleep * 1000);
}


static void	print_status(t_philos *current, char *msg)
{
	time_t	time;

	time = get_time();
	pthread_mutex_lock(&current->print);
	printf(" %ld %d %s\n", time - current->last_eat_time, current->id, msg);
	pthread_mutex_unlock(&current->print);
}


static void	takes_forks(t_status *status, t_philos *current)
{
	long int	time;

	time = get_time();
	pthread_mutex_lock(&current->left_fork);
	status->left_fork = true;
	printf("%ld %d %s", time - status->start_time, current->id, "has taken a fork\n");

	pthread_mutex_lock(&current->right_fork);
	status->right_fork = true;
	printf("%ld %d %s", time - status->start_time, current->id, "has taken a fork\n");
}

static void drops_forks(t_status *status, t_philos *current)
{
	pthread_mutex_unlock(&current->left_fork);
	status->left_fork = false;
	pthread_mutex_unlock(&current->right_fork);
	status->right_fork = false;
}

void	eating(t_status *status, t_philos *current)
{
	long int	time;

	time = get_time();
	takes_forks(status, current);
	pthread_mutex_lock(&current->print);
	printf("%ld %d %s", time - status->start_time, current->id, "is eating\n");
	pthread_mutex_unlock(&current->print);
	// current->last_eat_time = get_time();
	usleep(current->time_to_eat * 1000);
	drops_forks(status, current);
}

void	sleeping(t_philos *philo)
{
	print_status(philo, "is sleeping");
	usleep(philo->time_to_sleep * 1000);
}