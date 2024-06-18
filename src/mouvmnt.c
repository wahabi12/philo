/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvmnt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:05:14 by blatifat          #+#    #+#             */
/*   Updated: 2024/06/18 21:38:41 by blatifat         ###   ########.fr       */
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
	message(philo, "is thinking");
	pthread_mutex_unlock(&philo->donner->afficher);
}

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
