# Name of the executable
NAME = philo

# Source files
SRCS = ./main.c src/temps.c src/status_cheker2.c \
       src/necessaire.c src/mouvmnt.c src/list.c \
       src/initializ.c src/error_free.c \
       src/check.c src/philo.c

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
