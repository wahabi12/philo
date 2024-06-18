/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   necessaire.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 07:45:51 by blatifat          #+#    #+#             */
/*   Updated: 2024/06/18 12:20:41 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (result > INT_MAX / 10
			|| (result == INT_MAX / 10 && (*str - '0') > INT_MAX % 10))
		{
			return (-1);	
		}
		result = result * 10 + (*str - '0');
		str++;
	}
	return (sign * result);
}


void	message(t_mouvmt *philo, char *str)
{
	uint64_t	current_time;

	current_time = time_in_milis() - philo->donner->time_to_start;
	if (last_verification(philo))
		return ;
	printf("%llu %d %s\n", current_time, philo->num_philo, str);
}


/* void message(t_mouvmt *philo, char *str)
{
    uint64_t curren_time = time_in_milis() - philo->donner->time_to_start;

    if (philo->donner->death_statu)
        return;

    printf("%llu %d %s\n", curren_time, philo->num_philo, str);
}
 */
/* void	lock_affich_message(t_mouvmt *philo, char msg)
{
	pthread_mutex_lock(&philo->donner->afficher);
	message(philo, message);
	pthread_mutex_unlock(&philo->donner->afficher);
} */