
NAME = philo

SRCS = ./main.c src/temps.c src/status_cheker2.c \
       src/necessaire.c src/mouvmnt.c src/list.c \
       src/initializ.c src/error_free.c \
       src/check.c src/philo.c src/process.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -g -Wall -Wextra -Werror
INCS = -I ./includes/

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Linking object files to create the executable..."
	@$(CC) $(CFLAGS) $(INCS) $(OBJS) -o $(NAME)

%.o: %.c
	@echo "Compiling $< to $@..."
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	@echo "Cleaning up object files..."
	@$(RM) $(OBJS)

fclean: clean
	@echo "Removing executable..."
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
