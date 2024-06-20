/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 10:13:51 by blatifat          #+#    #+#             */
/*   Updated: 2024/06/20 17:10:41 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

uint64_t	time_in_milis(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * (uint64_t)1000)
		+ (current_time.tv_usec / 1000));
}

void	ft_usleep(uint64_t millsec)
{
	uint64_t	time;

	time = time_in_milis() + millsec;
	while (time_in_milis() != time)
		usleep(500);
}
