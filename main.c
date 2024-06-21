/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 03:12:03 by blatifat          #+#    #+#             */
/*   Updated: 2024/06/21 14:34:02 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

int	initialize_and_validate(int ac, char **av,
	t_donnee **donner, t_list **list)
{
	if (valid_num(ac, av) != 0)
		return (1);
	*donner = init(ac, av);
	if (*donner == NULL)
		return (1);
	if (verify_valu(ac, *donner) != 0)
	{
		free(*donner);
		return (1);
	}
	*list = list_creation(av, donner);
	if (*list == NULL)
	{
		free(*donner);
		return (1);
	}
	return (0);
}

void	simulatition_cleanup(t_donnee *donner, t_list *list)
{
	start_philos_threads(list);
	cleanup_mutex(list);
	free(donner);
}

int	main(int ac, char **av)
{
	t_donnee	*donner;
	t_list		*list;

	donner = NULL;
	list = NULL;
	if (initialize_and_validate(ac, av, &donner, &list) != 0)
		return (1);
	simulatition_cleanup(donner, list);
	return (0);
}
