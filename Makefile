NAME = philo

SRCS =

RM = rm -f

INCS = -I ./includes/

CC = cc

FLAGS = -g -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
		@${CC} $(FLAGS) $(SRC_B) -o checker
all: $(NAME)

clean:
		@$(RM) $(OBJS)

fclean: clean
		@$(RM) $(NAME)

re: fclean all

.PHONY : all clean fclean