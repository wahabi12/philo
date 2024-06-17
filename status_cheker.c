/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_cheker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 06:44:08 by blatifat          #+#    #+#             */
/*   Updated: 2024/06/17 00:40:41 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

/* int	death_status(t_mouvmt *philo)
{
	pthread_mutex_lock(&philo->donner->verify_if_death);
	if (philo->donner->death_statu == 0)
	{
		pthread_mutex_unlock(&philo->donner->verify_if_death);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&philo->donner->verify_if_death);
		return (1);
	}
}

int	eating_status(t_mouvmt *philo)
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
} */


int	verify_max_food_eaten(t_mouvmt *philo)
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

void	verify_death_of_philo(t_mouvmt *philo, uint64_t cur_time)
{
	pthread_mutex_lock(&philo->donner->verify_if_death);
	if (philo->donner->death_statu == 0)
	{
		philo->donner->death_statu = 1;
		pthread_mutex_lock(&philo->donner->afficher);
		if (verify_max_food_eaten(philo) == 0)
		{
			pthread_mutex_unlock(&philo->donner->afficher);
			pthread_mutex_unlock(&philo->donner->verify_if_death);
			return ;
		}
		printf("%llu %d, %s", cur_time, philo->num_philo, "Died");
		pthread_mutex_unlock(&philo->donner->afficher);
	}
	pthread_mutex_unlock(&philo->donner->verify_if_death);
}


