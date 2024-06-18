/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvmnt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:05:14 by blatifat          #+#    #+#             */
/*   Updated: 2024/06/18 12:20:46 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	he_sleep(t_mouvmt *philo)
{
	pthread_mutex_lock(&philo->donner->afficher);
	message(philo, "is sleeping");
	pthread_mutex_unlock(&philo->donner->afficher);
	ft_usleep(philo->donner->time_to_sleep);
}

void	thinkig(t_mouvmt *philo)
{
	pthread_mutex_lock(&philo->donner->afficher);
	/* printf("Before calling thinking function2\n"); */
	message(philo, "is thinking");
	/* printf("after calling thinking function2\n"); */
	pthread_mutex_unlock(&philo->donner->afficher);
}

/* void take_the_forks(t_philo *philo) {
    printf("Attempting to take the right fork...\n");
    pthread_mutex_lock(&(philo->fork_right));
    printf("Right fork taken.\n");

    printf("Attempting to take the left fork...\n");
    pthread_mutex_lock(philo->fork_left);
    printf("Left fork taken.\n");

    pthread_mutex_lock(&philo->data->printf);
    print_message(philo, "has taken a fork");
    print_message(philo, "has taken a fork");
    pthread_mutex_unlock(&philo->data->printf);
} */


void	hold_forks(t_mouvmt *philo)
{
	pthread_mutex_lock(&(philo->right_fork));
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->donner->afficher);
	message(philo, "has taken a fork");
	message(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->donner->afficher);
}

void	drop_forks(t_mouvmt *philo)
{
	pthread_mutex_unlock(&(philo->right_fork));
	pthread_mutex_unlock(&*(philo->left_fork));
}


/* void is_eating(t_philo *philo) {
    printf("Entering is_eating...\n");
    take_the_forks(philo);
    pthread_mutex_lock(&philo->data->printf);
    print_message(philo, "is eating");
    printf("hello\n");
    pthread_mutex_unlock(&philo->data->printf);
    ft_usleep(philo->data->time_eat);
    pthread_mutex_lock(&philo->data->meals_eaten);
    philo->data->max_meals_eaten--;
    pthread_mutex_unlock(&philo->data->meals_eaten);
    pthread_mutex_lock(&philo->data->time);
    philo->start_time = ft_gettime_millisec();
    pthread_mutex_unlock(&philo->data->time);
    drop_the_forks(philo);
    printf("Exiting is_eating...\n");
}
 */


void	eating(t_mouvmt *philo)
{
	hold_forks(philo);
	pthread_mutex_lock(&philo->donner->afficher);
	message(philo, "is eating");
	pthread_mutex_unlock(&philo->donner->afficher);
	ft_usleep(philo->donner->time_to_eat);
	pthread_mutex_lock(&philo->donner->food_to_eat);
	philo->donner->max_food_to_eat--;
	pthread_mutex_unlock(&philo->donner->food_to_eat);
	pthread_mutex_lock(&philo->donner->time);
	philo->time_to_start = time_in_milis();
	pthread_mutex_unlock(&philo->donner->time);
	drop_forks(philo);
}

/* int main() {
    // Initialisation des données
    t_donnee donner;
    pthread_mutex_init(&donner.afficher, NULL);
    pthread_mutex_init(&donner.food_to_eat, NULL);
    pthread_mutex_init(&donner.time, NULL);
    donner.max_food_to_eat = 10;
    donner.time_to_sleep = 10; // 1 seconde
    donner.time_to_eat = 500;    // 0.5 seconde
    
    // Initialisation du philosophe avec ses fourchettes (mutex)
    t_mouvmt philo;
    pthread_mutex_init(&philo.right_fork, NULL);
    philo.left_fork = &(donner.food_to_eat);
    philo.donner = &donner;
    philo.time_to_start = 0;
    
    // Exécution des actions des philosophes
    printf("Philosopher begins...\n");
    he_sleep(&philo);
    thinkig(&philo);
    hold_forks(&philo);
    eating(&philo);
    drop_forks(&philo);
    printf("Philosopher ends.\n");
    
    // Destruction des mutex
    pthread_mutex_destroy(&donner.afficher);
    pthread_mutex_destroy(&donner.food_to_eat);
    pthread_mutex_destroy(&donner.time);
    pthread_mutex_destroy(&philo.right_fork);
    
    return 0;
} */