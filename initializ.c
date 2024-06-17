/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 10:26:43 by blatifat          #+#    #+#             */
/*   Updated: 2024/06/14 05:04:29 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_donnee	*init(int ac, char **av)
{
	t_donnee	*data;

	if (ac < 5 || ac > 6)
		return (NULL);
	data = malloc(sizeof(t_donnee));
	if (!data)
		return (NULL);
	data->finish = 0;
	data->num_of_philosophers = atoi(av[1]);
	data->time_to_start = time_in_ms();
	data->death_statu = 0;
	data->time_to_die = atoi(av[2]);
	data->time_to_eat = atoi(av[2]);
	data->time_to_sleep = atoi(av[4]);
	if (ac == 6)
		data->max_food_to_eat = (atoi(av[5]) * data->num_of_philosophers);
	else
		data->max_food_to_eat = -1;
	pthread_mutex_init(&(data->afficher), NULL);
	pthread_mutex_init(&(data->verify_if_death), NULL);
	pthread_mutex_init(&(data->food_to_eat), NULL);
	pthread_mutex_init(&(data->time), NULL);
	return (data);
}

t_mouvmt	*creat_philo(char **av, t_donnee **donner)
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
		philo = creat_philo(av, donner);
		philo->num_philo = i + 1;
		ajout_a_list(list, &philo);
		i++;
	}
}
