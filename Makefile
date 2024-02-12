SRC_SERV = server.c
SRC_CL = client.c

LIBFT = ft_printf.c ft_putnbrs.c ft_utils.c

HS = minitalk.h

OBJS_SERV = ${SRC_SERV:.c=.o}
DEPS_SERV = ${SRC_SERV:.c=.d}

OBJS_CL = ${SRC_CL:.c=.o}
DEPS_CL = ${SRC_CL:.c=.d}

OBJS_LIBFT = ${LIBFT:.c=.o}
DEPS_LIBFT = ${LIBFT:.c=.d}

CC = gcc
FLAGS = -Wall -Wextra -Werror -MMD
RM = rm -f

SERVER = server
CLIENT = client

all : $(LIBFT) $(SERVER) $(CLIENT)

-include ${DEPS_LIBFT} ${DEPS_SERV} ${DEPS_CL}

%.o : %.c Makefile
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

$(SERVER) : $(OBJS_LIBFT) $(OBJS_SERV)
	$(CC) $(FLAGS) $(OBJS_LIBFT) $(OBJS_SERV) -o $(SERVER)

$(CLIENT) : $(OBJS_LIBFT) $(OBJS_CL)
	$(CC) $(FLAGS) $(OBJS_LIBFT) $(OBJS_CL) -o $(CLIENT)

clean :
	$(RM) $(OBJS_SERV) $(OBJS_CL) $(DEPS_SERV) $(DEPS_CL) $(OBJS_LIBFT) $(DEPS_LIBFT)

fclean : clean
	$(RM) $(SERVER) $(CLIENT)

bonus : $(LIBFT) $(SERVER) $(CLIENT)

re : fclean all

.PHONY: all clean fclean re
