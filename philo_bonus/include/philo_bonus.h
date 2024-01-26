#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <signal.h>
# include <wait.h>

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
	sem_t			*forks;
	sem_t			*print;
	sem_t			*eat;
	sem_t			*dead;
	sem_t			*nbr_eat;
	pid_t			*pid;
}					t_status;

typedef struct s_philo
{
	int				id;
	long			time_last_eat;
	int				had_dinner;
	t_status		*status;
	sem_t			*forks;
	// sem_t			*right_fork;
}					t_philo;

//##################################### INIT ###################################

t_bool				check_args(int argc, char **argv);
void				init_status(int argc, char **argv, t_status *status);
void				init_philos(t_philo *philo, t_status *status);

//##################################### THREADS ################################

void				one_philo(t_philo *philo);
void				start_semaphores(t_philo *philos, t_status *status);
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
void				clean_up(t_status *status);

#endif