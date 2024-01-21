#include "../include/philo.h"

void    init_status(int argc, char **argv, t_status *status)
{
    int i;

    i = -1;
    status->nbr_philo = (int)ft_atol(argv[1]);
    status->time_to_die = (int)ft_atol(argv[2]);
    status->time_to_eat = (int)ft_atol(argv[3]);
    status->time_to_sleep = (int)ft_atol(argv[4]);
    if (argc == 6)
        status->nbr_must_eat = (int)ft_atol(argv[5]);
    else
        status->nbr_must_eat = -1;
    status->is_dead = 0;
    status->start = get_time_now();

    pthread_mutex_init(&status->printf, NULL);
    pthread_mutex_init(&status->eat, NULL);
    pthread_mutex_init(&status->dead, NULL);
    pthread_mutex_init(&status->nbr_eat, NULL);

    status->forks = malloc(sizeof(pthread_mutex_t) * status->nbr_philo);
    while (++i < status->nbr_philo)
        pthread_mutex_init(&status->forks[i], NULL);
}

void    init_philos(t_philo *philo, t_status *status)
{
    int i;

    i = -1;
    // philo = malloc(sizeof(t_philo) * status->nbr_philo);
    while (++i < status->nbr_philo)
    {
        philo[i].id = i + 1;
        philo[i].times_ate = 0;
        philo[i].time_last_eat = 0;
        philo[i].status = status;
        philo[i].left_fork = &status->forks[i];
        philo[i].right_fork = &status->forks[(i + 1) % status->nbr_philo];
    }
}