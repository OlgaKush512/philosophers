/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okushnir <okushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 19:12:23 by okushnir          #+#    #+#             */
/*   Updated: 2021/11/05 19:12:25 by okushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (2);
	else
	{
		i = 1;
		while (i < argc)
		{
			j = 0;
			while (j < (int)ft_strlen(argv[i]))
			{
				if (!ft_isdigit(argv[i][j]))
					return (3);
				j++;
			}
			i++;
		}
	}
	return (1);
}

int	check_int(long arg)
{
	if (arg > 2147483647)
		return (5);
	else if (arg < 0)
		return (6);
	else
		return (1);
}

int	check_init_param_repeat(t_data *my_data, char **argv)
{
	if (check_int(ft_atoi(argv[5])) == 1)
		my_data->nb_repeat = (int)ft_atoi(argv[5]);
	else
		return (check_int(ft_atoi(argv[5])));
	return (1);
}
