/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:33:17 by blatifat          #+#    #+#             */
/*   Updated: 2024/06/21 15:44:59 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* int	perfom_action(t_mouvmt *philo, void (*action)(t_mouvmt *))
{
	if (last_checking(philo) == 1)
		return (1);
	action(philo);
	return (last_checking(philo));
}
 */
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
