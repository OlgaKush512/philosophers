/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okushnir <okushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 19:13:37 by okushnir          #+#    #+#             */
/*   Updated: 2021/11/05 19:13:38 by okushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	check_philos(t_philo *philos, int nb)
{
	int		i;
	long	start;
	int		id;
	int		nbr_meal;

	start = philos[0].data->tm_start;
	nbr_meal = 0;
	i = 0;
	while (i < nb)
	{
		pthread_mutex_lock(&(philos[i].mut_nbr_meal));
		nbr_meal += philos[i].nbr_meal;
		pthread_mutex_unlock(&(philos[i].mut_nbr_meal));
		id = philos[i].id_ph;
		check_time(&philos[i]);
		if (check_alive(philos) == 0)
		{
			pthread_mutex_lock(&philos->data->mut_print);
			printf("%ld philo n.%d died\n", (get_time() - start), id);
			pthread_mutex_unlock(&philos->data->mut_print);
			return (-1);
		}
		i++;
	}
	return (nbr_meal);
}

int	monitor_ph(t_philo	*philos)
{
	int		nb;
	int		nbr_meal;

	nb = philos[0].data->nb_philo;
	while (1)
	{
		nbr_meal = check_philos(philos, nb);
		if (nbr_meal == 0)
			return (0);
		else if (nbr_meal == -1)
			return (-1);
		usleep(800);
	}
	return (1);
}

void	check_time(t_philo *philo)
{
	long	cur_meal;
	long	res;

	cur_meal = get_time() - philo->data->tm_start;
	pthread_mutex_lock(&philo->data->mut_last_meal);
	res = cur_meal - philo->last_meal;
	pthread_mutex_unlock(&philo->data->mut_last_meal);
	if (check_alive(philo) == 0)
		return ;
	if (res > (philo->data->tm_die + 2) && philo->nbr_meal != 0)
	{
		pthread_mutex_lock(&philo->data->mut_live);
		philo->data->live = 0;
		pthread_mutex_unlock(&philo->data->mut_live);
		philo->data->ph_died = philo->id_ph;
		put_fork(philo);
	}
}
