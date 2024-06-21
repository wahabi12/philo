/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 22:19:11 by blatifat          #+#    #+#             */
/*   Updated: 2024/06/21 18:03:13 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	collec_thread(t_mouvmt *philo, t_list *list)
{
	t_mouvmt	*cur;

	cur = philo;
	while (cur != NULL)
	{
		if (pthread_join(cur->thread, NULL) != 0)
		{
			error_msg("Error", list);
			break ;
		}
		if (cur == list->begining)
			break ;
		cur = cur->prev;
	}
}

int	start_philos_threads(t_list *philo_list)
{
	t_mouvmt	*cur;
	t_mouvmt	*last_philo;

	cur = philo_list->begining;
	while (cur)
	{
		if (pthread_create(&(cur->thread), NULL, &process,
				(void *)cur) != 0)
			return (error_msg("Error", philo_list));
		if (cur == philo_list->end)
			break ;
		cur = cur->next;
	}
	last_philo = cur;
	cur = philo_list->begining;
	while (cur)
	{
		if (last_checking(cur))
			break ;
		cur = cur->next;
	}
	collec_thread(last_philo, philo_list);
	return (0);
}

void	for_one_philo(t_mouvmt *philo)
{
	time_t	time;

	time = time_in_milis();
	pthread_mutex_lock(&philo->right_fork);
	if (philo->donner->num_of_philosophers == 1)
		printf("%lu %d has taken a fork\n",
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
