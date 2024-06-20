/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:33:17 by blatifat          #+#    #+#             */
/*   Updated: 2024/06/20 16:42:50 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	perfom_action(t_mouvmt *philo, void (*action)(t_mouvmt *))
{
	if (last_checking(philo) == 1)
		return (1);
	action(philo);
	return (last_checking(philo));
}

void	*process(void *arg)
{
	t_mouvmt	*philo;

	philo = (t_mouvmt *)arg;
	philo_thinking(philo);
	while (death_eating_status(philo, CHECK_MEALS_EATEN) != 0
		&& death_eating_status(philo, CHECK_DEATH_STATUS) == 0
		&& (philo->donner->num_of_philosophers != 1))
	{
		if (perfom_action(philo, eating) == 1)
			return (NULL);
		eating(philo);
		if (perfom_action(philo, he_sleep) == 1)
			return (NULL);
		he_sleep(philo);
		if (perfom_action(philo, thinkig) == 1)
			return (NULL);
		thinkig(philo);
	}
	for_one_philo(philo);
	return (arg);
}


