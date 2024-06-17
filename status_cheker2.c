/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_cheker2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 07:48:42 by blatifat          #+#    #+#             */
/*   Updated: 2024/06/17 00:40:15 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* int	death_eat_status(t_mouvmt *philo)
{
	pthread_mutex_lock(&philo->donner->food_to_eat);
	if (philo->donner->max_food_to_eat == 0)
	{
		pthread_mutex_unlock(&philo->donner->food_to_eat);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&philo->donner->food_to_eat);
		return (1);
	}
}

int	verify_food_and_death(t_mouvmt *philo)
{
	int	death_statu;
	int	food_to_eat;

	death_statu = 0;
	food_to_eat = 0;
	pthread_mutex_lock(&philo->donner->food_to_eat);
	food_to_eat = (philo->eating_time == philo->donner->max_food_to_eat);
	pthread_mutex_unlock(&philo->donner->food_to_eat);
	pthread_mutex_lock(&philo->donner->verify_if_death);
	death_statu = philo->donner->death_statu;
	pthread_mutex_unlock(&philo->donner->verify_if_death);
	if (food_to_eat || death_statu)
		return (1);
	return (0);
}

int	verify_time_death(t_mouvmt *philo, time_t curr_time)
{
	time_t	time;

	time = 0;
	pthread_mutex_lock(&philo->donner->time);
	time = time_in_ms() - philo->time_to_start;
	pthread_mutex_unlock(&philo->donner->time);
	pthread_mutex_lock(&philo->donner->verify_if_death);
	if (time > philo->donner->time_to_die)
	{
		verify_death_of_philo(philo, curr_time);
		pthread_mutex_unlock(&philo->donner->verify_if_death);
	return (1);
	}
	if (philo->donner->death_statu)
	{
		pthread_mutex_unlock(&philo->donner->verify_if_death);
		return (1);
	}
	pthread_mutex_unlock(&philo->donner->verify_if_death);
	return (0);
}

int	last_verification(t_mouvmt *philo)
{
	time_t	curr_time;

	curr_time = 0;
	if (verify_food_and_death(philo))
		return (1);
	curr_time = time_in_ms() - philo->donner->time_to_start;
	if (verify_time_death(philo, curr_time))
		return (1);
	return (0);
}
 */

/* int	last_verification(t_mouvmt *philo)
{
	uint64_t	time;
	uint64_t	current_time;

	pthread_mutex_lock(&philo->donner->time);
	time = time_in_ms() - philo->time_to_start;
	pthread_mutex_unlock(&philo->donner->time);
	current_time = time_in_ms() - philo->donner->time_to_start;
	pthread_mutex_lock(&philo->donner->verify_if_death);
	if (death_eating_status(philo) == 0 && philo->donner->death_statu == 0)
	{
		philo->donner->death_statu = 1;
		pthread_mutex_unlock(&philo->donner->verify_if_death);
		return (1);
	}
	if (time > philo->donner->time_to_die)
		verify_death_of_philo(philo, current_time);
	if (philo->donner->death_statu == 1)
	{
		pthread_mutex_unlock(&philo->donner->verify_if_death);
		return (1);
	}
	pthread_mutex_unlock(&philo->donner->verify_if_death);
	return (0);
} */




/*  int main()
{
    t_donnee data;
    t_mouvmt philosophers[MAX_PHILOSOPHERS];

    // Initialize data
    pthread_mutex_init(&data.afficher, NULL);
    pthread_mutex_init(&data.verify_if_death, NULL);
    pthread_mutex_init(&data.food_to_eat, NULL);
    pthread_mutex_init(&data.eating, NULL);
    pthread_mutex_init(&data.time, NULL);
    data.time_to_sleep = 1000;
    data.time_to_die = 5000;
    data.time_to_eat = 2000;
    data.time_to_start = time_in_ms();
    data.finish = 0;
    data.max_food_to_eat = 3;
    data.death_statu = 0;
    data.num_of_philosophers = MAX_PHILOSOPHERS;

    // Initialize philosophers
    for (int i = 0; i < MAX_PHILOSOPHERS; i++)
    {
        philosophers[i].donner = &data;
        philosophers[i].eating_time = 0;
        philosophers[i].num_philo = i + 1;
        pthread_mutex_init(&philosophers[i].right_fork, NULL);
        if (i == 0)
            philosophers[i].left_fork = &philosophers[MAX_PHILOSOPHERS - 1].right_fork;
        else
            philosophers[i].left_fork = &philosophers[i - 1].right_fork;

        printf("Initial state:\nPhilosopher %d: Death status: Alive, Meals eaten: %d\n",
               philosophers[i].num_philo, philosophers[i].eating_time);
    }

    // Simulate eating and checking for multiple meals
    for (int meal = 1; meal <= 5; meal++)
    {
        printf("\nAfter meal %d:\n", meal);
        for (int i = 0; i < MAX_PHILOSOPHERS; i++)
        {
            philosophers[i].eating_time += 1;
            if (last_verification(&philosophers[i]))
            {
                printf("Philosopher %d has died or reached max meals.\n", philosophers[i].num_philo);
            }
            else
            {
                printf("Philosopher %d: Death status: Alive, Meals eaten: %d\n",
                       philosophers[i].num_philo, philosophers[i].eating_time);
            }
        }
    }

    // Clean up
    for (int i = 0; i < MAX_PHILOSOPHERS; i++)
    {
        pthread_mutex_destroy(&philosophers[i].right_fork);
    }
    pthread_mutex_destroy(&data.afficher);
    pthread_mutex_destroy(&data.verify_if_death);
    pthread_mutex_destroy(&data.food_to_eat);
    pthread_mutex_destroy(&data.eating);
    pthread_mutex_destroy(&data.time);

    return 0;
} */








int	last_verification(t_mouvmt *philo)
{
	uint64_t	time;
	uint64_t	current_time;
	int		death_statu;

	death_statu = 0;
	pthread_mutex_lock(&philo->donner->time);
	time = time_in_milis() - philo->time_to_start;
	pthread_mutex_unlock(&philo->donner->time);
	current_time = time_in_milis() - philo->donner->time_to_start;
	pthread_mutex_lock(&philo->donner->verify_if_death);
	if (death_eating_status(philo, CHECK_DEATH_STATUS) == 0
		&& philo->donner->death_statu == 0)
	{
		philo->donner->death_statu = 1;
		death_statu = 1;
	}
	if (time > philo->donner->time_to_die)
		verify_death_of_philo(philo, current_time);
	if (philo->donner->death_statu == 1)
		death_statu = 1;
	pthread_mutex_unlock(&philo->donner->verify_if_death);
	return (death_statu);
}
