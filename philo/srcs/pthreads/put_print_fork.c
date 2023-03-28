/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_print_fork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okushnir <okushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 19:13:51 by okushnir          #+#    #+#             */
/*   Updated: 2021/11/05 19:13:52 by okushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	print_fork(t_philo *philo, long st)
{
	if (check_alive(philo) == 1)
	{
		pthread_mutex_lock(&philo->data->mut_print);
		printf("%ld Philosopher %d has taken a fork\n", (get_time() - st),
			philo->id_ph);
		pthread_mutex_unlock(&philo->data->mut_print);
	}
}

void	put_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->right_fork->mut_fork));
	if (philo->right_fork->taken == 1)
		philo->right_fork->taken = 0;
	pthread_mutex_unlock(&(philo->right_fork->mut_fork));
	pthread_mutex_lock(&(philo->left_fork->mut_fork));
	if (philo->left_fork->taken == 1)
		philo->left_fork->taken = 0;
	pthread_mutex_unlock(&(philo->left_fork->mut_fork));
}
