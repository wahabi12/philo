/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 10:26:43 by blatifat          #+#    #+#             */
/*   Updated: 2024/06/21 15:57:38 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_donnee	*init(int ac, char **av)
{
	t_donnee	*donner;

	if (ac < 5 || ac > 6)
		return (NULL);
	donner = malloc(sizeof(t_donnee));
	if (!donner)
		return (NULL);
	donner->finish = 0;
	donner->num_of_philosophers = atoi(av[1]);
	donner->time_to_start = time_in_milis();
	donner->death_statu = 0;
	donner->time_to_die = atoi(av[2]);
	donner->time_to_eat = atoi(av[3]);
	donner->time_to_sleep = atoi(av[4]);
	if (ac == 6)
		donner->max_food_to_eat = (atoi(av[5]) * donner->num_of_philosophers);
	else
		donner->max_food_to_eat = -1;
	pthread_mutex_init(&(donner->afficher), NULL);
	pthread_mutex_init(&(donner->verify_if_death), NULL);
	pthread_mutex_init(&(donner->food_to_eat), NULL);
	pthread_mutex_init(&(donner->time), NULL);
	return (donner);
}

t_mouvmt	*creat_philo(t_donnee **donner)
{
	t_mouvmt	*philo;

	philo = malloc(sizeof(t_mouvmt));
	if (!philo)
		return (NULL);
	*philo = (t_mouvmt)
	{
		.eating_time = 0,
		.donner = *donner,
		.num_philo = 0,
		.time_to_sleep = (*donner)->time_to_sleep,
		.time_to_eat = (*donner)->time_to_eat,
		.time_to_die = (*donner)->time_to_die,
		.time_to_start = (*donner)->time_to_start,
		.next = NULL,
		.prev = NULL
	};
	pthread_mutex_init(&(philo->right_fork), NULL);
	return (philo);
}

void	initialization_philo(char **av, t_donnee **donner, t_list **list)
{
	int			i;
	t_mouvmt	*philo;

	i = 0;
	while (i < atoi(av[1]))
	{
		philo = creat_philo(donner);
		philo->num_philo = i + 1;
		ajout_a_list(list, &philo);
		i++;
	}
}
