SRCS = 

HS = 

OBJS = ${SRCS:.c=.o}
DEPS = ${SRCS:.c=.d}

CC = gcc
FLAGS = -Wall -Wextra -Werror
RM = rm -f

NAME = server client

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) -c $< -o $(<:.c:.o)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean $(NAME)


.PHONY: all clean fclean re