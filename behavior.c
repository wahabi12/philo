/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behavior.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 01:22:22 by blatifat          #+#    #+#             */
/*   Updated: 2024/06/17 09:18:51 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	for_one_philo(t_mouvmt *philo)
{
	uint64_t	cur_time;

	if (philo->donner->num_of_philosophers == 1)
	{
		pthread_mutex_lock(&philo->right_fork);
		cur_time = time_in_milis();
		printf("%llu %d has taken a fork\n", cur_time - philo->donner->time_to_start, philo->num_philo);
	}
}

void philo_that_think(t_mouvmt *philo)
{
    int num_philo = philo->num_philo;
    int total_philo = philo->donner->num_of_philosophers;

    if (total_philo != 1 && 
        (num_philo % 2 == 0 || (num_philo == total_philo && num_philo % 2 == 1)))
    {
        thinkig(philo);
        ft_usleep(1);
    }
}


void	philo_thinking(t_mouvmt *philo)
{
	int	num_philo;
	int	total_of_philo;

	num_philo = philo->num_philo;
	total_of_philo = philo->donner->num_of_philosophers;
	if (total_of_philo != 1 &&
		(num_philo % 2 == 0 || (num_philo == total_of_philo && num_philo % 2 == 1)))
	{
			thinkig(philo);
			ft_usleep(2);
	}
}

void	*routine(void *arg)
{
	t_mouvmt	*philo;

	philo = (t_mouvmt *)arg;
	philo_that_think(philo);
	while (death_eating_status(philo, CHECK_MEALS_EATEN) != 0
		&& death_eating_status(philo, CHECK_DEATH_STATUS) == 0
		&& (philo->donner->num_of_philosophers != 1))
	{
		if (last_verification(philo) == 1)
			return (NULL);
		    eating(philo);
		if (last_verification(philo) == 1)
			return (NULL);
		he_sleep(philo);
		if (last_verification(philo) == 1)
			return (NULL);
/* 		thinkig(philo);
		if (last_verification(philo) == 1)
			return (NULL); */
	}
	for_one_philo(philo);
	return (arg);
}


int main() {
    // Exemple d'initialisation des données communes
    t_donnee donner;
    donner.num_of_philosophers = 5; // Exemple: 5 philosophes
    
    // Exemple d'initialisation des philosophes
    t_mouvmt philos[5];
    for (int i = 0; i < 5; i++) {
        philos[i].donner = &donner;
        // Initialisation d'autres membres du philosophe si nécessaire
    }
    
    // Exemple de création des threads pour chaque philosophe
    pthread_t threads[5];
    for (int i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, routine, &philos[i]);
    }
    
    // Attente de la fin de tous les threads
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }
    
    return 0;
}
