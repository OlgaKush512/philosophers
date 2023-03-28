/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okushnir <okushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 19:11:57 by okushnir          #+#    #+#             */
/*   Updated: 2021/11/05 19:12:00 by okushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	message_error(int ret)
{
	if (ret == 2)
		write(2, "Error!\nUsage: ./philo <4 or 5 parameters>\n", 43);
	else if (ret == 3)
		write(2, "Error!\nOnly digital parameters\n", 32);
	else if (ret == 4)
		write(2, "Error!\nFailed to create thread\n", 32);
	else if (ret == 5)
	{
		write(2, "Error!\nThe value of the parameter ", 35);
		write(2, "exceeds the threshold MAXINT\n", 30);
	}
	else if (ret == 6)
		write(2, "Error!\nOnly positive numbers can be parameters\n", 48);
}
