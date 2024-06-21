/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:16:47 by blatifat          #+#    #+#             */
/*   Updated: 2024/06/21 19:48:44 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_msg(t_list *list)
{
	t_mouvmt	*cur;
	t_mouvmt	*tmp;

	if (!list || !list->begining)
		return ;
	cur = list->begining;
	tmp = cur;
	while (tmp != NULL)
	{
		cur = tmp->next;
		free(tmp);
		tmp = cur;
		if (tmp == list->begining)
			break ;
	}
	free(list);
}

void	free_extra_list(t_list *list)
{
	size_t		i;
	t_mouvmt	*tmp;

	i = 0;
	while (i < list->size)
	{
		tmp = list->begining;
		list->begining = list->begining->next;
		free(tmp);
		i++;
	}
	free(list);
}

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
	free_extra_list(list);
}

int	error_msg(const char *string, t_list *list)
{
	printf("%s\n", string);
	cleanup_mutex(list);
	free(list);
	return (1);
}
