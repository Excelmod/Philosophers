SRCS = ./philo/philo.c
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Werror -Wextra -pthread
HEADERS = -I philo
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
