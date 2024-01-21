# ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>

typedef enum e_bool
{
    false,
    true
}	t_bool;

typedef struct s_status
{
    int				nbr_philo;
    int				time_to_die;
    int				time_to_eat;
    int				time_to_sleep;
    int				nbr_must_eat;
    int				is_dead;
    long			start;
    pthread_mutex_t	*forks;
    pthread_mutex_t	printf;
    pthread_mutex_t	eat;
    pthread_mutex_t	dead;
    pthread_mutex_t nbr_eat;
}					t_status;

typedef struct s_philo
{
    int				id;
    int				times_ate;
    long			time_last_eat;
    t_status		*status;
    pthread_mutex_t	*left_fork;
    pthread_mutex_t	*right_fork;
}					t_philo;

//##################################### INIT ###################################

t_bool	    check_args(int argc, char **argv);
void        init_status(int argc, char **argv, t_status *status);
void        init_philos(t_philo *philo, t_status *status);

//##################################### UTILS ##################################

long int	ft_atol(const char *str);
void	    *ft_calloc(size_t count, size_t size);
long int    get_time_now(void);

# endif