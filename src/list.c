/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 04:37:32 by blatifat          #+#    #+#             */
/*   Updated: 2024/06/17 06:24:57 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ajout_a_list(t_list **list, t_mouvmt **philo) // add_philo_to_list
{
	t_list		*lst;
	t_mouvmt	*nw_philo;

	lst = *list;
	nw_philo = *philo;
	if (lst->begining == NULL)
	{
		lst->begining = nw_philo;
		lst->end = nw_philo;
		nw_philo->next = nw_philo;
		nw_philo->prev = nw_philo;
	}
	else
	{
		nw_philo->prev = lst->end;
		nw_philo->next = lst->begining;
		lst->end->next = nw_philo;
		lst->begining->prev = nw_philo;
		lst->end = nw_philo;
	}
	lst->size++;
}

t_list	*list_initializ(void)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	if (list)
	{
		list->begining = NULL;
		list->end = NULL;
		list->size = 0;
	}
	return (list);
}

void	set_left_fork(t_list *list)
{
	t_mouvmt	*curr;

	curr = list->begining;
	while (curr != list->end)
	{
		curr->left_fork = &(curr->prev->right_fork);
		curr = curr->next;
	}
	curr->left_fork = &(curr->prev->right_fork);
}

t_list	*list_creation(char **av, t_donnee **donner)
{
	t_list	*list;

	list = list_initializ();
	initialization_philo(av, donner, &list);
	set_left_fork(list);
	return (list);
}


/* void print_list(t_list *list) {
    if (list == NULL || list->size == 0) {
        printf("Empty list\n");
        return;
    }
}
 */