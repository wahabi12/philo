/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:16:47 by blatifat          #+#    #+#             */
/*   Updated: 2024/06/18 09:52:30 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_mutex(t_list *list)
{
	t_mouvmt	*curr_philo;
	t_mouvmt	*next_philo;

	if (list && list->begining)
	{
		curr_philo = list->begining;
		next_philo = curr_philo->next;
		while (next_philo != list->begining)
		{
			pthread_mutex_destroy(&curr_philo->right_fork);
			curr_philo = next_philo;
			next_philo = curr_philo->next;
		}
		pthread_mutex_destroy(&list->begining->donner->afficher);
		pthread_mutex_destroy(&list->begining->donner->time);
		pthread_mutex_destroy(&list->begining->donner->verify_if_death);
		pthread_mutex_destroy(&list->begining->donner->food_to_eat);
	}
}

int error_msg(const char *string, t_list *list)
{
	printf(stderr, "%s\n", string);
	cleanup_mutex(list);
	free(list);
	return (1);
}