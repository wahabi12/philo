/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 22:19:11 by blatifat          #+#    #+#             */
/*   Updated: 2024/06/20 09:40:39 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	for_one_philo(t_mouvmt *philo)
{
	uint64_t	time;

	time = time_in_milis();
	pthread_mutex_lock(&philo->right_fork);
	if (philo->donner->num_of_philosophers == 1)
		printf("%llu %d has taken a fork\n",
			time - philo->donner->time_to_start, philo->num_philo);
}

void	philo_thinking(t_mouvmt *philo)
{
	int	num_philo;
	int	total_of_philo;

	num_philo = philo->num_philo;
	total_of_philo = philo->donner->num_of_philosophers;
	if (total_of_philo != 1
		&& (num_philo % 2 == 0
			|| (num_philo == total_of_philo && num_philo % 2 == 1)))
	{
		thinkig(philo);
		ft_usleep(1);
	}
}

/* void	aaction_process(t_mouvmt *philo)
{
	if (last_checking(philo) == 1)
		return ;
	eating(philo);
	if (last_checking(philo) == 1)
		return ;
	he_sleep(philo);
	if (last_checking(philo) == 1)
		return ;
	thinkig(philo);
}

void	*process(void *arg)
{
	t_mouvmt	*philo;

	philo = (t_mouvmt *)arg;
	philo_thinking(philo);
	while (death_eating_status(philo, CHECK_MEALS_EATEN) != 0
		&& death_eating_status(philo, CHECK_DEATH_STATUS) == 0
		&& philo->donner->num_of_philosophers != 1)
	{
		aaction_process(philo);
	}
	for_one_philo(philo);
	return (NULL);
}
 */

void	*process(void *arg)
{
	t_mouvmt	*philo;

	philo = (t_mouvmt *)arg;
	philo_thinking(philo);
	while (death_eating_status(philo, CHECK_MEALS_EATEN) != 0
		&& death_eating_status(philo, CHECK_DEATH_STATUS) == 0
		&& (philo->donner->num_of_philosophers != 1))
	{
		if (last_checking(philo) == 1)
			return (NULL);
		eating(philo);
		if (last_checking(philo) == 1)
			return (NULL);
		he_sleep(philo);
		if (last_checking(philo) == 1)
			return (NULL);
		thinkig(philo);
		if (last_checking(philo) == 1)
			return (NULL);
	}
	for_one_philo(philo);
	return (arg);
}

