/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_cheker2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 07:48:42 by blatifat          #+#    #+#             */
/*   Updated: 2024/06/20 11:04:35 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	death_eating_status(t_mouvmt *philo, t_check_type type)
{
	int				result;
	pthread_mutex_t	*mutex;

	result = 0;
	if (type == CHECK_DEATH_STATUS)
	{
		mutex = &philo->donner->verify_if_death;
		pthread_mutex_lock(mutex);
		result = philo->donner->death_statu;
		pthread_mutex_unlock(mutex);
	}
	if (type == CHECK_MEALS_EATEN)
	{
		mutex = &philo->donner->food_to_eat;
		pthread_mutex_lock(mutex);
		result = philo->donner->max_food_to_eat;
		pthread_mutex_unlock(mutex);
	}
	if (result == 0)
		return (0);
	else
		return (1);
}

int	verify_mx_food(t_mouvmt *philo)
{
	int	food_to_eat;
	int	max_food_to_eat;

	pthread_mutex_lock(&philo->donner->food_to_eat);
	food_to_eat = philo->eating_time;
	max_food_to_eat = philo->donner->max_food_to_eat;
	pthread_mutex_unlock(&philo->donner->food_to_eat);
	if (food_to_eat >= max_food_to_eat)
		return (0);
	else
		return (1);
}

void	verify_death_philo(t_mouvmt *philo, uint64_t current_time)
{
	if (philo->donner->death_statu == 0)
	{
		philo->donner->death_statu = 1;
		pthread_mutex_lock(&philo->donner->afficher);
		if (verify_mx_food(philo) == 0)
		{
			pthread_mutex_unlock(&philo->donner->afficher);
			pthread_mutex_unlock(&philo->donner->verify_if_death);
			return ;
		}
		printf("%llu %d %s\n", current_time, philo->num_philo, "died");
		pthread_mutex_unlock(&philo->donner->afficher);
	}
}

/* void	verify_death_philo(t_mouvmt *philo, uint64_t cur_time)
{
	pthread_mutex_lock(&philo->donner->verify_if_death);
	if (philo->donner->death_statu == 0)
	{
		pthread_mutex_unlock(&philo->donner->verify_if_death);
		return ;
	}
	pthread_mutex_lock(&philo->donner->afficher);
	if (philo->eating_time >= philo->donner->max_food_to_eat)
	{
		printf("%llu %d %s\n", cur_time, philo->num_philo, "died");
		philo->donner->death_statu = 0;
	}
	pthread_mutex_unlock(&philo->donner->afficher);
	pthread_mutex_unlock(&philo->donner->verify_if_death);
} */


int	last_checking(t_mouvmt *philo)
{
	uint64_t	time;
	uint64_t	current_time;

	pthread_mutex_lock(&philo->donner->time);
	time = time_in_milis() - philo->time_to_start;
	pthread_mutex_unlock(&philo->donner->time);
	current_time = time_in_milis() - philo->donner->time_to_start;
	pthread_mutex_lock(&philo->donner->verify_if_death);
	if (death_eating_status(philo, CHECK_MEALS_EATEN) == 0
		&& philo->donner->death_statu == 0)
	{
		philo->donner->death_statu = 1;
		pthread_mutex_unlock(&philo->donner->verify_if_death);
		return (1);
	}
	if (time > philo->donner->time_to_die)
		verify_death_philo(philo, current_time);
	if (philo->donner->death_statu == 1)
	{
		pthread_mutex_unlock(&philo->donner->verify_if_death);
		return (1);
	}
	pthread_mutex_unlock(&philo->donner->verify_if_death);
	return (0);
}

/* int	last_checking(t_mouvmt *philo)
{
	uint64_t	time;
	uint64_t	current_time;

	pthread_mutex_lock(&philo->donner->time);
	time = time_in_milis() - philo->time_to_start;
	pthread_mutex_unlock(&philo->donner->time);
	current_time = time_in_milis() - philo->donner->time_to_start;
	pthread_mutex_lock(&philo->donner->verify_if_death);
	if (death_eating_status(philo, CHECK_MEALS_EATEN) == 0 && philo->donner->death_statu == 0)
	{
		philo->donner->death_statu = 1;
		pthread_mutex_unlock(&philo->donner->verify_if_death);
		return (1);
	}
	if (time > philo->donner->time_to_die)
		verify_death_philo(philo, current_time);
	if (philo->donner->death_statu == 1)
	{
		pthread_mutex_unlock(&philo->donner->verify_if_death);
		return (1);
	}
	pthread_mutex_unlock(&philo->donner->verify_if_death);
	return (0);
} */

