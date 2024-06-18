/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 22:19:11 by blatifat          #+#    #+#             */
/*   Updated: 2024/06/18 15:12:29 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* void one_philo(t_philo *philo) {
    uint64_t time = ft_gettime_millisec();

    // Lock the right fork unconditionally
    pthread_mutex_lock(&philo->fork_right);

    // Check if there's only one philosopher and print message
    if (philo->data->numbers_of_philo == 1) {
        printf("%llu %d has taken a fork\n", time - philo->data->start_time, philo->philo_number);
    }
} */

void	for_one_philo(t_mouvmt *philo)
{
	uint64_t	time;

	time = time_in_milis();
	pthread_mutex_lock(&philo->right_fork);
	if (philo->donner->num_of_philosophers == 1)
		printf("%llu %d has taken a fork\n",
			time - philo->donner->time_to_start, philo->num_philo);
}

/* void	for_one_philo(t_mouvmt *philo)
{
	uint64_t	cur_time;
	uint64_t	time;

	if (philo->donner->num_of_philosophers == 1)
	{
		pthread_mutex_lock(&philo->right_fork);
		cur_time = time_in_milis();
		time = cur_time - philo->donner->time_to_start;
		printf("%llu %d has taken a fork\n",
			time, philo->num_philo);
	}
} */

void	philo_thinking(t_mouvmt *philo)
{
	int	num_philo;
	int	total_of_philo;

	num_philo = philo->num_philo;
	total_of_philo = philo->donner->num_of_philosophers;
	if (total_of_philo != 1
		&& (num_philo % 2 == 0
			|| (num_philo == total_of_philo && num_philo % 2 == 1)))
	{
		thinkig(philo);
		ft_usleep(1);
	}
}

void	aaction_process(t_mouvmt *philo)
{
	if (last_checking(philo) == 1)
		return ;
	eating(philo);
	if (last_checking(philo) == 1)
		return ;
	he_sleep(philo);
	if (last_checking(philo) == 1)
		return ;
	thinkig(philo);
}

void	*process(void *arg)
{
	t_mouvmt	*philo;

	philo = (t_mouvmt *)arg;
	philo_thinking(philo);
	while (verify_statu_food(philo) != 0
		&& verify_statu_death(philo) == 0
		&& philo->donner->num_of_philosophers != 1)
	{
		aaction_process(philo);
	}
	for_one_philo(philo);
	return (NULL);
}




