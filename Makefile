NAME = philo

SRCS = ./main.c src/temps.c src/status_cheker2.c \
		src/necessaire.c src/mouvmnt.c src/list.c \
		src/initializ.c src/error_free.c \
		src/check.c src/behavior.c src/philo.c \

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