/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behavior.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 01:22:22 by blatifat          #+#    #+#             */
/*   Updated: 2024/06/17 03:14:05 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* void	for_one_philo(t_mouvmt *philo)
{
	uint64_t	cur_time;

	if (philo->donner->num_of_philosophers == 1)
	{
		pthread_mutex_lock(&philo->right_fork);
		cur_time = time_in_milis();
		printf("%llu %d has taken a fork\n");
	}
} */

/* void philo_that_think(t_mouvmt *philo)
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
 */

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

int main(void)
{
    t_donnee donner;
    t_mouvmt philo;

    // Initialize donner
    donner.num_of_philosophers = 5; // Example value
    donner.time_to_start = (uint64_t)time(NULL) * 1000;

    // Initialize philosopher
    philo.num_philo = 2; // Example value
    philo.donner = &donner;

    // Test the philo_that_think function
    philo_thinking(&philo);

    return 0;
}