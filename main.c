/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 03:12:03 by blatifat          #+#    #+#             */
/*   Updated: 2024/06/17 02:49:44 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void one_philo(t_mouvmt *philo)
{
	if (philo->donner->num_of_philosophers == 1)
	{
		pthread_mutex_lock(&philo->right_fork);
		uint64_t current_time = time_in_milis();
		printf("%llu %d has taken a fork\n", 
		       current_time - philo->donner->time_to_start, philo->num_philo);
	}
}


int main(void)
{
	// Initialize donner
	t_donnee donner;
	donner.time_to_start = time_in_milis();
	donner.num_of_philosophers = 1;

	// Initialize philosopher
	t_mouvmt philo;
	philo.num_philo = 1;
	philo.donner = &donner;
	pthread_mutex_init(&philo.right_fork, NULL);

	// Test one_philo function
	one_philo(&philo);

	// Clean up
	pthread_mutex_destroy(&philo.right_fork);

	return 0;
}
