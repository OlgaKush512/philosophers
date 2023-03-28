/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okushnir <okushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 19:11:44 by okushnir          #+#    #+#             */
/*   Updated: 2021/11/05 19:11:47 by okushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_data			my_data;
	pthread_mutex_t	mutex;
	int				ret;

	ret = check_args(argc, argv);
	pthread_mutex_init(&mutex, NULL);
	if (ret == 1)
	{
		init_data(&my_data);
		ret = fill_up_data(&my_data, argc, argv);
		if (ret == 1)
			ret = init_app(&my_data);
		else
		{
			message_error(ret);
			pthread_mutex_destroy(&mutex);
			return (0);
		}
	}
	else
		message_error(ret);
	pthread_mutex_destroy(&mutex);
	return (0);
}
