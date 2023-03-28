/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okushnir <okushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 19:13:44 by okushnir          #+#    #+#             */
/*   Updated: 2021/11/05 19:13:45 by okushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	mut_destroy(t_data **my_data, t_philo *philos, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		pthread_mutex_destroy(&(philos[i]).mut_nbr_meal);
		i++;
	}
	pthread_mutex_destroy(&(*my_data)->mut_print);
	pthread_mutex_destroy(&(*my_data)->mut_last_meal);
	pthread_mutex_destroy(&(*my_data)->mut_live);
}

int	check_alive(t_philo *philo)
{
	int	res;

	pthread_mutex_lock(&philo->data->mut_live);
	res = philo->data->live;
	pthread_mutex_unlock(&philo->data->mut_live);
	return (res);
}

void	reinit_last_meal(t_philo **philo, long start)
{
	pthread_mutex_lock(&(*philo)->data->mut_last_meal);
	(*philo)->last_meal = get_time() - start;
	pthread_mutex_unlock(&(*philo)->data->mut_last_meal);
}

int	check_nbr_meal(t_philo **philo)
{
	pthread_mutex_lock(&(*philo)->mut_nbr_meal);
	(*philo)->nbr_meal--;
	pthread_mutex_unlock(&(*philo)->mut_nbr_meal);
	if ((*philo)->nbr_meal == 0)
	{
		put_fork(*philo);
		return (0);
	}
	return (1);
}

void	routine_start(t_philo **philo, long st)
{
	int	id;

	id = (*philo)->id_ph;
	reinit_last_meal(philo, st);
	if (check_alive(*philo) == 1)
	{
		pthread_mutex_lock(&(*philo)->data->mut_print);
		printf("%ld Philosopher %d is eating\n", get_time() - st, id);
		pthread_mutex_unlock(&(*philo)->data->mut_print);
	}
}
