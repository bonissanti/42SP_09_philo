#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_bool
{
	false,
	true
}					t_bool;

typedef struct s_status
{
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_must_eat;
	int				had_dined;
	int				is_dead;
	int				out_of_food;
	long			start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	eat;
	pthread_mutex_t	dead;
	pthread_mutex_t	nbr_eat;
}					t_status;

typedef struct s_philo
{
	int				id;
	long			time_last_eat;
	int				had_dinner;
	t_status		*status;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_philo;

//##################################### INIT ###################################

t_bool				check_args(int argc, char **argv);
void				init_status(int argc, char **argv, t_status *status);
void				init_philos(t_philo *philo, t_status *status);

//##################################### THREADS ################################

void				one_philo(t_philo *philo);
void				start_threads(t_philo *philos, t_status *status);
void				*monitor(void *arg);

//##################################### ACTIONS ################################

void				eating(t_philo *philo);
void				thinking(t_philo *philo);
void				sleeping(t_philo *philo);

//##################################### UTILS ##################################

void				*ft_calloc(size_t count, size_t size);
void				print_actions(t_philo *philo, char *msg);
void				print_death(t_philo *philo, char *msg);
t_bool				philo_dined(t_philo *philo);
size_t				atosz(const char *str);
long int			get_time_now(void);
void				free_status(t_status *status);

#endif