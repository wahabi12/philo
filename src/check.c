/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 05:03:45 by blatifat          #+#    #+#             */
/*   Updated: 2024/06/18 12:21:09 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	digit_num(const char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (1);
		str++;
	}
	return (0);
}

int	valid_num(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("%s : %s\n", STR_ERR_INPUT_DIGIT, argv[1]);
		return (EXIT_FAILURE);
	}
	if ((digit_num(argv[1]) == 1) || (digit_num(argv[2]) == 1))
	{
		printf("%s : %s\n", STR_ERR_INPUT_POFLOW, STR_MAX_PHILOS);
		return (EXIT_FAILURE);
	}
	if ((digit_num(argv[3]) == 1) || (digit_num(argv[4]) == 1))
	{
		printf("%s : %s\n", STR_ERR_INPUT_POFLOW, STR_MAX_PHILOS);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	verify_valu(int ac, t_donnee *donner)
{
	if (ac == 6)
	{
		if (donner->max_food_to_eat == 0 || donner->max_food_to_eat < 0)
		{
			printf("%s : %s\n", STR_ERR_INPUT_POFLOW, STR_MAX_PHILOS);
			return (EXIT_FAILURE);
		}
	}
	if (donner->num_of_philosophers > MAX_PHILOS
		|| donner->num_of_philosophers <= 0)
	{
		printf("%s : %s\n", STR_ERR_INPUT_POFLOW, STR_MAX_PHILOS);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
