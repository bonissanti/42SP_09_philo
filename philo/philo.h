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

typedef struct s_philos
{
	int				id;
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	long int		last_eat_time;
	pthread_mutex_t	print;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
	struct s_philos	*next;
}					t_philos;

typedef struct s_status
{
	int				id;
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int 			num_meals;
	long int		start_time;
	t_philos		*head;
	t_bool			died;
	t_bool			left_fork;
	t_bool			right_fork;
	t_bool			*running;
}					t_status;

//################################## init ######################################

t_status				*get_status(void);
t_philos			*add_philo(t_status *status);
t_philos			*init_philo(t_status *status);

//################################## handle ####################################

int 				handle_philo(t_status *status, t_philos *philo);

//################################## actions ###################################

long int    		get_time(void);
void    			print_time(t_status *status);
void				thinking(t_status *status, t_philos *current);

#endif