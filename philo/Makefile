SRCS = philo.c arguments_handling.c exit_handling.c ft_itoa.c ft_putstr_fd.c ft_putendl_fd.c
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Werror -Wextra -pthread
HEADERS = -I .
NAME = philo

all : $(NAME)

%.o : %.c
	gcc -c $(CFLAGS) $(HEADERS) $< -o $@

$(NAME) : $(OBJS)
	gcc -pthread -o $@ $(OBJS) $(HEADERS)

clean:
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : re all clean fclean
