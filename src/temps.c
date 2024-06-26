/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 10:13:51 by blatifat          #+#    #+#             */
/*   Updated: 2024/06/21 17:58:39 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

time_t	time_in_milis(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(time_t millsec)
{
	time_t	time;

	time = time_in_milis() + millsec;
	while (time_in_milis() != time)
		usleep(500);
}
