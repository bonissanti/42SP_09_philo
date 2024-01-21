#include "../include/philo.h"

int main(int argc, char **argv)
{
    t_philo *philo;
    t_status *status;
    
    if (!check_args(argc, argv + 1))
        return (1);
    status = malloc(sizeof(t_status));
    init_status(argc, argv, status);
    philo = malloc(sizeof(t_philo) * status->nbr_philo);
    init_philos(philo, status);
}

    // função para criar threads, passo o status como &status
    // função para dar free em tudo, passo o status como &status

// int	main(int argc, char **argv)
// {
//     t_philo	*philo;

//     if (argc < 5 || argc > 6)
//         return (ft_error("Error: wrong number of arguments\n"));
//     philo = ft_init_philo(argc, argv);
//     if (!philo)
//         return (ft_error("Error: malloc failed\n"));
//     if (ft_init_mutex(philo))
//         return (ft_error("Error: mutex init failed\n"));
//     if (ft_init_thread(philo))
//         return (ft_error("Error: thread init failed\n"));
//     ft_free_philo(philo);
//     return (0);
// }