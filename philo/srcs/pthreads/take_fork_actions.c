/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_fork_actions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okushnir <okushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 19:14:00 by okushnir          #+#    #+#             */
/*   Updated: 2021/11/05 19:14:02 by okushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	take_right_fork(t_philo *philo)
{
	if (philo->right_fork->taken == 0)
	{
		philo->right_fork->taken = 1;
		return (1);
	}
	else
		return (0);
}

int	take_left_fork(t_philo *philo)
{
	if (philo->left_fork->taken == 0)
	{
		philo->left_fork->taken = 1;
		return (1);
	}
	else
		return (0);
}

void	right_handed(t_philo *philo, long st, int continu)
{
	while (continu)
	{
		pthread_mutex_lock(&(philo->right_fork->mut_fork));
		if (take_right_fork(philo))
			continu = 0;
		pthread_mutex_unlock(&(philo->right_fork->mut_fork));
		usleep(TIME);
	}
	print_fork(philo, st);
	continu = 1;
	if (philo->data->nb_philo > 1)
	{
		while (continu)
		{
			pthread_mutex_lock(&(philo->left_fork->mut_fork));
			if (take_left_fork(philo))
				continu = 0;
			pthread_mutex_unlock(&(philo->left_fork->mut_fork));
			usleep(TIME);
		}
		print_fork(philo, st);
	}
}

void	left_handed(t_philo *philo, long st, int continu)
{
	while (continu)
	{
		pthread_mutex_lock(&(philo->left_fork->mut_fork));
		if (take_left_fork(philo))
			continu = 0;
		pthread_mutex_unlock(&(philo->left_fork->mut_fork));
		usleep(TIME);
	}
	print_fork(philo, st);
	continu = 1;
	while (continu)
	{
		pthread_mutex_lock(&(philo->right_fork->mut_fork));
		if (take_right_fork(philo))
			continu = 0;
		pthread_mutex_unlock(&(philo->right_fork->mut_fork));
		usleep(TIME);
	}
	print_fork(philo, st);
}

void	take_fork(t_philo *philo)
{
	long	start;
	int		continu;

	continu = 1;
	check_time(philo);
	start = philo->data->tm_start;
	if (check_alive(philo) == 1)
	{
		if (!(is_even(philo->id_ph)))
			right_handed(philo, start, continu);
		else
		{
			usleep(100);
			left_handed(philo, start, continu);
		}
	}
}
