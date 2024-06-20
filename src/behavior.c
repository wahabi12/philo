/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behavior.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 01:22:22 by blatifat          #+#    #+#             */
/*   Updated: 2024/06/20 08:45:57 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	join_threads(t_mouvmt *philo, t_list *list)
{
	while (philo)
	{
		if (pthread_join(philo->thread, NULL) != 0)
			error_msg("Error", list);
		if (philo == list->begining)
			break ;
		philo = philo->prev;
	}
}

int	create_and_start_threads(t_list *philo_list)
{
	t_mouvmt	*current;
	t_mouvmt	*current2;

	current = philo_list->begining;
	while (current)
	{
		if (pthread_create(&(current->thread), NULL, &process,
				(void *)current) != 0)
			return (error_msg("Error", philo_list));
		if (current == philo_list->end)
			break ;
		current = current->next;
	}
	current2 = current;
	current = philo_list->begining;
	while (current)
	{
		if (last_checking(current))
			break ;
		current = current->next;
	}
	join_threads(current2, philo_list);
	return (0);
}
