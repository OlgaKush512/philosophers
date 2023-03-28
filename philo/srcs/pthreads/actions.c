/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okushnir <okushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 19:13:18 by okushnir          #+#    #+#             */
/*   Updated: 2021/11/05 19:13:22 by okushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	start_phread(t_philo *ph, int nb)
{
	int	i;

	i = 0;
	if (nb == 1)
	{
		if (pthread_create(&ph[i].th_philo, NULL, &routine_one, &ph[i]) != 0)
			printf("Failed to create thread\n");
	}
	else
	{
		while (i < nb)
		{
			if (pthread_create(&ph[i].th_philo, NULL, &routine, &ph[i]) != 0)
				printf("Failed to create thread\n");
			i++;
		}
	}
}

int	init_app(t_data *my_data)
{
	int		i;
	int		nb;
	t_philo	*ph;

	ph = NULL;
	ph = init_philo(my_data);
	my_data->tm_start = get_time();
	nb = my_data->nb_philo;
	i = 0;
	start_phread(ph, nb);
	i = 0;
	monitor_ph(ph);
	while (i < nb)
		if (pthread_join(ph[i++].th_philo, NULL) != 0)
			printf("Failed to finish execution\n");
	mut_destroy(&my_data, ph, nb);
	free(ph);
	free(my_data->forks);
	return (0);
}

void	*routine_one(void *arg)
{
	t_philo		*philo;
	long		st;

	philo = (t_philo *)arg;
	st = philo->data->tm_start;
	take_fork(philo);
	waiting_tm(philo->data->tm_die);
	pthread_mutex_lock(&philo->data->mut_print);
	printf("%ld philo n.%d died\n", (get_time() - st), philo->id_ph);
	pthread_mutex_unlock(&philo->data->mut_print);
	return (0);
}

void	*routine(void *arg)
{
	t_philo		*philo;
	long		st;

	philo = (t_philo *)arg;
	st = philo->data->tm_start;
	while (1)
	{
		check_time(philo);
		take_fork(philo);
		if (check_alive(philo) == 1)
		{
			routine_start(&philo, st);
			waiting_tm(philo->data->tm_eat);
			if (philo->data->nb_repeat >= 0)
				if (check_nbr_meal(&philo) != 1)
					return (0);
		}
		put_fork(philo);
		sleep_think(philo);
		if (check_alive(philo) != 1)
			break ;
	}
	return (0);
}

void	sleep_think(t_philo *arg)
{
	long	st;
	int		id;

	st = arg->data->tm_start;
	id = arg->id_ph;
	if (check_alive(arg) == 1)
	{
		pthread_mutex_lock(&arg->data->mut_print);
		printf("%ld Philosopher %d is sleeping\n", get_time() - st, id);
		pthread_mutex_unlock(&arg->data->mut_print);
		waiting_tm(arg->data->tm_sleep);
		if (check_alive(arg) == 1)
		{
			pthread_mutex_lock(&arg->data->mut_print);
			printf("%ld Philosopher %d is is thinking\n", get_time() - st, id);
			pthread_mutex_unlock(&arg->data->mut_print);
			usleep(100);
		}
		else
			put_fork(arg);
	}
}
