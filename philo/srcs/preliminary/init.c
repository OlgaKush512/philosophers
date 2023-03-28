/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okushnir <okushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 19:12:41 by okushnir          #+#    #+#             */
/*   Updated: 2021/11/05 19:12:51 by okushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	init_data(t_data *philo)
{
	philo->nb_philo = 0;
	philo->tm_die = 0;
	philo->tm_eat = 0;
	philo->tm_sleep = 0;
	philo->nb_repeat = -1;
	philo->live = 0;
	philo->ph_died = 0;
	philo->forks = NULL;
	pthread_mutex_init(&philo->mut_print, NULL);
}

int	fill_up_data(t_data *my_data, int argc, char **argv)
{
	if (check_int(ft_atoi(argv[1])) == 1)
		my_data->nb_philo = (int)ft_atoi(argv[1]);
	else
		return (check_int(ft_atoi(argv[1])));
	if (check_int(ft_atoi(argv[2])) == 1)
		my_data->tm_die = ft_atoi(argv[2]);
	else
		return (check_int(ft_atoi(argv[2])));
	if (check_int(ft_atoi(argv[3])) == 1)
		my_data->tm_eat = ft_atoi(argv[3]);
	else
		return (check_int(ft_atoi(argv[3])));
	if (check_int(ft_atoi(argv[4])) == 1)
		my_data->tm_sleep = ft_atoi(argv[4]);
	else
		return (check_int(ft_atoi(argv[4])));
	my_data->live = 1;
	init_fork(my_data);
	init_mut(my_data);
	if (argc == 6)
		return (check_init_param_repeat(my_data, argv));
	return (1);
}

void	init_mut(t_data *my_data)
{
	pthread_mutex_init(&my_data->mut_print, NULL);
	pthread_mutex_init(&my_data->mut_last_meal, NULL);
	pthread_mutex_init(&my_data->mut_live, NULL);
}

void	*init_fork(t_data *my_data)
{
	int	nb;
	int	i;

	nb = my_data->nb_philo;
	i = 0;
	my_data->forks = (t_fork *)malloc(sizeof(t_fork) * nb);
	if (my_data->forks == NULL)
		return (NULL);
	while (i < nb)
	{
		my_data->forks[i].n_fork = i + 1;
		pthread_mutex_init(&my_data->forks[i].mut_fork, NULL);
		pthread_mutex_init(&my_data->forks[i].unmut_fork, NULL);
		my_data->forks[i].taken = 0;
		i++;
	}
	return (0);
}

t_philo	*init_philo(t_data *my_data)
{
	int		nb;
	int		i;
	t_philo	*philos;

	nb = my_data->nb_philo;
	i = 0;
	philos = (t_philo *)malloc(sizeof(t_philo) * nb);
	if (philos == NULL)
		return (NULL);
	while (i < nb)
	{
		philos[i].id_ph = i + 1;
		philos[i].right_fork = &my_data->forks[i];
		if (i != nb - 1)
			philos[i].left_fork = &my_data->forks[i + 1];
		else
			philos[i].left_fork = &my_data->forks[0];
		philos[i].last_meal = 0;
		philos[i].nbr_meal = my_data->nb_repeat;
		philos[i].well_fed = 0;
		philos[i].data = my_data;
		pthread_mutex_init(&(philos[i].mut_nbr_meal), NULL);
		i++;
	}
	return (philos);
}
