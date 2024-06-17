/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 04:37:32 by blatifat          #+#    #+#             */
/*   Updated: 2024/06/14 06:35:12 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ajout_a_list(t_list **list, t_mouvmt **philo)
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

/* int main(int argc, char **argv) {
	if (argc < 5 || argc > 6) {
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
		return 1;
	}

	t_donnee *donner = malloc(sizeof(t_donnee));
	if (!donner) {
		return 1;
	}
	donner->num_of_philosophers = atoi(argv[1]);
	donner->time_to_die = atoi(argv[2]);
	donner->time_to_eat = atoi(argv[3]);
	donner->time_to_sleep = atoi(argv[4]);
	donner->time_to_start = time_in_ms();
	donner->max_food_to_eat = (argc == 6) ? atoi(argv[5]) : -1;

	t_list *list = list_creation(argv, &donner);
	if (!list) {
		return 1;
	}

	// Test print to verify list creation
	t_mouvmt *current = list->begining;
	do {
		printf("Philosopher %d: time_to_die = %ld, time_to_eat = %ld, time_to_sleep = %ld\n",
			   current->num_philo, current->time_to_die, current->time_to_eat, current->time_to_sleep);
		current = current->next;
	} while (current != list->begining);

	// Free allocated memory (add necessary cleanup code here)
	// ...

	return 0;
} */


/* int main(int argc, char **argv) {
	if (argc < 5 || argc > 6) {
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
		return 1;
	}

	t_donnee *donner = malloc(sizeof(t_donnee));
	if (!donner) {
		return 1;
	}
	donner->num_of_philosophers = atoi(argv[1]);
	donner->time_to_die = (t_time)atoi(argv[2]);
	donner->time_to_eat = (t_time)atoi(argv[3]);
	donner->time_to_sleep = (t_time)atoi(argv[4]);
	donner->time_to_start = time_in_ms();
	donner->max_food_to_eat = (argc == 6) ? atoi(argv[5]) : -1;

	t_list *list = list_creation(argv, &donner);
	if (!list) {
		return 1;
	}

	// Test print to verify list creation
	t_mouvmt *current = list->begining;
	do {
		printf("Philosopher %d: time_to_die = %llu, time_to_eat = %llu, time_to_sleep = %llu\n",
			   current->num_philo, (unsigned long long)current->time_to_die, (unsigned long long)current->time_to_eat, (unsigned long long)current->time_to_sleep);
		current = current->next;
	} while (current != list->begining);

	// Free allocated memory (add necessary cleanup code here)
	// ...

	return 0;
} */