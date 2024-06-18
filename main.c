/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 03:12:03 by blatifat          #+#    #+#             */
/*   Updated: 2024/06/18 22:50:25 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

int	initialize_and_validate(int ac, char **av, t_donnee **donner, t_list **list)
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
	create_and_start_threads(list);
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


/* # Name of the executable
NAME = philo

# Source files
SRCS = ./main.c src/temps.c src/status_cheker2.c \
       src/necessaire.c src/mouvmnt.c src/list.c \
       src/initializ.c src/error_free.c \
       src/check.c src/behavior.c src/philo.c

# Object files
OBJS = $(SRCS:.c=.o)

# Compiler and flags
CC = cc
CFLAGS = -g -Wall -Wextra -Werror
INCS = -I ./includes/

# Remove command
RM = rm -f

# Default rule
all: $(NAME)

# Rule to build the executable
$(NAME): $(OBJS)
	@echo "Linking object files to create the executable..."
	@$(CC) $(CFLAGS) $(INCS) $(OBJS) -o $(NAME)

# Rule to build object files
%.o: %.c
	@echo "Compiling $< to $@..."
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

# Clean up object files
clean:
	@echo "Cleaning up object files..."
	@$(RM) $(OBJS)

# Clean up all generated files
fclean: clean
	@echo "Removing executable..."
	@$(RM) $(NAME)

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re
 */