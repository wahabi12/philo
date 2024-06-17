/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvmnt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:05:14 by blatifat          #+#    #+#             */
/*   Updated: 2024/06/17 02:29:58 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	he_sleep(t_mouvmt *philo)
{
	pthread_mutex_lock(&philo->donner->afficher);
	printf("Before calling sleping function3\n");
	message(philo, "is sleeping");
	printf("Before calling sleping function3\n");
	pthread_mutex_unlock(&philo->donner->afficher);
	ft_usleep(philo->donner->time_to_sleep);
}

void	thinkig(t_mouvmt *philo)
{
	pthread_mutex_lock(&philo->donner->afficher);
	printf("Before calling thinking function2\n");
	message(philo, "is thinking");
	printf("Before calling thinking function2\n");
	pthread_mutex_unlock(&philo->donner->afficher);
}

void	hold_forks(t_mouvmt *philo)
{
	pthread_mutex_lock(&(philo->right_fork));
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->donner->afficher);
	printf("Before calling fork function\n");
	message(philo, "has taken a fork");
	message(philo, "has taken a fork");
	printf("After calling fork function\n");
	pthread_mutex_unlock(&philo->donner->afficher);
}

void	drop_forks(t_mouvmt *philo)
{
	pthread_mutex_unlock(&(philo->right_fork));
	pthread_mutex_unlock(philo->left_fork);
}

void	eating(t_mouvmt *philo)
{
	hold_forks(philo);
	printf("Before calling eating function1\n");
	message(philo, "is eating");
	printf("After calling eating function1\n");
	ft_usleep(philo->donner->time_to_eat);
	pthread_mutex_lock(&philo->donner->food_to_eat);
	philo->donner->max_food_to_eat--;
	pthread_mutex_unlock(&philo->donner->food_to_eat);
	pthread_mutex_lock(&philo->donner->time);
	philo->time_to_start = time_in_milis();
	pthread_mutex_unlock(&philo->donner->food_to_eat);
	drop_forks(philo);
}


int main(void)
{
    t_donnee donner;
    t_mouvmt philo;

    // Initialize the shared data
    donner.time_to_start = time_in_milis();
    donner.time_to_eat = 1000; // Philosopher eats for 1000 ms
    donner.max_food_to_eat = 3; // Example value
    pthread_mutex_init(&donner.afficher, NULL);
    pthread_mutex_init(&donner.food_to_eat, NULL);
    pthread_mutex_init(&donner.time, NULL);

    // Initialize the philosopher
    philo.num_philo = 1;
    philo.donner = &donner;
    philo.time_to_start = donner.time_to_start;
    pthread_mutex_init(&philo.right_fork, NULL);
    pthread_mutex_t fork_left;
    pthread_mutex_init(&fork_left, NULL);
    philo.left_fork = &fork_left;

    // Test the behaviors
    eating(&philo);
    he_sleep(&philo);
    thinkig(&philo);

    // Clean up
    pthread_mutex_destroy(&donner.afficher);
    pthread_mutex_destroy(&donner.food_to_eat);
    pthread_mutex_destroy(&donner.time);
    pthread_mutex_destroy(&philo.right_fork);
    pthread_mutex_destroy(&fork_left);

    return 0;
}
