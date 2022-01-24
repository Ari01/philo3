NAME	=	philo

SRCS	=	main.c \
			utils.c \
			parser.c \
			threads.c \
			check_end_sim.c \
			eat.c

OBJS	=	$(SRCS:.c=.o)

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -pthread

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $@

debug:		$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -fsanitize=thread -g -o $@

.c.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean:
			rm -rf $(OBJS)

fclean:		clean
			rm -rf $(NAME)
			rm -rf .*.swp

re:			fclean all

.PHONY:		all clean fclean re
