NAME := philo
CC := cc
CFLAGS := -Wall -Wextra -Werror -g
SRCS := philo_allocs.c philo_end.c philo_forks.c \
        philo_frees.c philo_libft.c philo_utils.c \
        philo_utils2.c philo.c
OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -pthread -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
