/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okushnir <okushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 19:11:34 by okushnir          #+#    #+#             */
/*   Updated: 2021/11/05 19:11:37 by okushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h> //memset()
# include <unistd.h>
# include <pthread.h>
# include <signal.h>
# include <time.h>
# include <sys/time.h> //gettimeofday()

# define TIME 10

typedef struct s_time
{
	struct timeval	tv1;
	struct timeval	tv2;
	struct timeval	dtv;
}				t_time;

typedef struct s_fork
{
	int				n_fork;
	pthread_mutex_t	mut_fork;
	pthread_mutex_t	unmut_fork;
	int				taken;
}				t_fork;

typedef struct s_data
{
	int				live;
	int				ph_died;
	long			nb_philo;
	long			tm_die;
	long			tm_eat;
	long			tm_sleep;
	int				nb_repeat;
	long			tm_start;
	t_fork			*forks;
	pthread_mutex_t	mut_print;
	pthread_mutex_t	mut_last_meal;
	pthread_mutex_t	mut_live;
}				t_data;

typedef struct s_philo
{
	int				done;
	int				id_ph;
	int				well_fed;
	pthread_t		th_philo;
	pthread_mutex_t	mut_nbr_meal;
	t_fork			*right_fork;
	t_fork			*left_fork;
	int				nbr_meal;
	long			last_meal;
	t_data			*data;
}				t_philo;

typedef struct s_tab
{
	t_philo		*tab_philos;
}				t_tab;

/*srcs/preliminary/check.c*/
int		check_args(int argc, char **argv);
int		check_int(long arg);
int		check_init_param_repeat(t_data *my_data, char **argv);

/*srcs/errors/errors.c*/
void	message_error(int ret);

/*srcs/preliminary/init.c*/
void	init_data(t_data *philo);
int		fill_up_data(t_data *my_data, int argc, char **argv);
void	init_mut(t_data *my_data);
void	*init_fork(t_data *my_data);
t_philo	*init_philo(t_data *my_data);

/*srcs/preliminary/fonctions_std.c*/
long	ft_atoi(const char *str);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
int		is_even(int nb);

/*srcs/preliminary/time.c*/
long	get_time(void);
void	waiting_tm(long tm);

/*srcs/pthreads/actions.c*/

int		init_app(t_data *my_data);
void	start_phread(t_philo *ph, int nb);
void	*routine_one(void *arg);
void	*routine(void *arg);
void	sleep_think(t_philo *arg);

/*srcs/pthreads/monitoring.c*/
int		check_philos(t_philo *philos, int nb);
int		monitor_ph(t_philo	*philos);
void	check_time(t_philo *philo);

/*srcs/pthreads/take_fork_actions.c*/
int		take_right_fork(t_philo *philo);
int		take_left_fork(t_philo *philo);
void	right_handed(t_philo *philo, long st, int continu);
void	left_handed(t_philo *philo, long st, int continu);
void	take_fork(t_philo *philo);

/*srcs/pthreads/put_print_fork.c*/
void	print_fork(t_philo *philo, long st);
void	put_fork(t_philo *philo);

/*srcs/pthreads/mutex_actions.c*/
void	mut_destroy(t_data **my_data, t_philo *philos, int nb);
int		check_alive(t_philo *philo);
void	reinit_last_meal(t_philo **philo, long start);
int		check_nbr_meal(t_philo **philo);
void	routine_start(t_philo **philo, long st);

#endif
