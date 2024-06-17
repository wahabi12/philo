/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 10:13:51 by blatifat          #+#    #+#             */
/*   Updated: 2024/06/17 01:11:04 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* uint64_t	time_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	return ((time.tv_sec * (uint64_t)1000000) + time.tv_usec);
} */

uint64_t	time_in_ms(void)
{
	struct timeval	curren_time;

	gettimeofday(&curren_time, NULL);
	return ((curren_time.tv_sec * (uint64_t)1000000) + curren_time.tv_usec);
}

uint64_t time_in_milis(void)
{
	return (time_in_ms() / 1000);
}

void	ft_usleep(uint64_t ms)
{
	uint64_t	time;
	time = time_in_milis() + ms;
	while (time_in_milis() != time)
		usleep(500);
}

