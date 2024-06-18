/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_cheker2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 07:48:42 by blatifat          #+#    #+#             */
/*   Updated: 2024/06/18 21:19:27 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	verify_statu_death(t_mouvmt *philo)
{
	int	status;

	pthread_mutex_lock(&philo->donner->verify_if_death);
	status = philo->donner->death_statu;
	pthread_mutex_unlock(&philo->donner->verify_if_death);
	return (status != 0);
}

int	verify_statu_food(t_mouvmt *philo)
{
	int	status;

	pthread_mutex_lock(&philo->donner->food_to_eat);
	status = philo->donner->max_food_to_eat;
	pthread_mutex_unlock(&philo->donner->food_to_eat);
	return (status != 0);
}

int	verify_mx_food(t_mouvmt *philo)
{
	int	food_to_eat;
	int	eat_more;

	pthread_mutex_lock(&philo->donner->food_to_eat);
	food_to_eat = philo->eating_time;
	eat_more = (food_to_eat < philo->donner->max_food_to_eat);
	pthread_mutex_unlock(&philo->donner->food_to_eat);
	return (eat_more);
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
	uint16_t	cur_time;
	int			must_die;

	must_die = 0;
	pthread_mutex_lock(&philo->donner->time);
	cur_time = time_in_milis() - philo->time_to_start;
	pthread_mutex_unlock(&philo->donner->time);
	pthread_mutex_lock(&philo->donner->verify_if_death);
	if (philo->eating_time >= philo->donner->max_food_to_eat)
	{
		must_die = 1;
		philo->donner->death_statu = 0;
	}
	if (!must_die && cur_time > philo->donner->time_to_die)
	{
		must_die = 1;
		verify_death_philo(philo, cur_time);
	}
	pthread_mutex_unlock(&philo->donner->verify_if_death);
	return (must_die);
}
