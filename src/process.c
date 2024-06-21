/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:33:17 by blatifat          #+#    #+#             */
/*   Updated: 2024/06/21 18:57:17 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	last_checking(t_mouvmt *philo)
{
	time_t	time;
	time_t	current_time;

	pthread_mutex_lock(&philo->donner->time);
	time = time_in_milis() - philo->time_to_start;
	pthread_mutex_unlock(&philo->donner->time);
	current_time = time_in_milis() - philo->donner->time_to_start;
	pthread_mutex_lock(&philo->donner->verify_if_death);
	if (death_eating_status(philo, CHECK_MEALS_EATEN) == 0
		&& philo->donner->death_statu == 0)
	{
		philo->donner->death_statu = 1;
		pthread_mutex_unlock(&philo->donner->verify_if_death);
		return (1);
	}
	if (time > philo->donner->time_to_die)
		verify_death_philo(philo, current_time);
	if (philo->donner->death_statu == 1)
	{
		pthread_mutex_unlock(&philo->donner->verify_if_death);
		return (1);
	}
	pthread_mutex_unlock(&philo->donner->verify_if_death);
	return (0);
}

void	*process(void *arg)
{
	t_mouvmt	*philo;

	philo = (t_mouvmt *)arg;
	philo_thinking(philo);
	while (1)
	{
		if (last_checking(philo) == 1)
			break ;
		if (death_eating_status(philo, CHECK_MEALS_EATEN) == 0
			|| death_eating_status(philo, CHECK_DEATH_STATUS) != 0
			|| philo->donner->num_of_philosophers == 1)
			break ;
		eating(philo);
		if (last_checking(philo) == 1)
			break ;
		he_sleep(philo);
		if (last_checking(philo) == 1)
			break ;
		thinkig(philo);
	}
	if (philo->donner->num_of_philosophers == 1)
		for_one_philo(philo);
	return (arg);
}
