SRC_SERV = server.c
SRC_CL = client.c

SRC_SERV_BONUS = server_bonus.c
SRC_CL_BONUS = client_bonus.c

LIBFT = ft_printf.c ft_putnbrs.c ft_utils.c

HS = minitalk.h

OBJS_SERV = ${SRC_SERV:.c=.o}
DEPS_SERV = ${SRC_SERV:.c=.d}

OBJS_CL = ${SRC_CL:.c=.o}
DEPS_CL = ${SRC_CL:.c=.d}

OBJS_SERV_BONUS = ${SRC_SERV_BONUS:.c=.o}
DEPS_SERV_BONUS = ${SRC_SERV_BONUS:.c=.d}

OBJS_CL_BONUS = ${SRC_CL_BONUS:.c=.o}
DEPS_CL_BONUS = ${SRC_CL_BONUS:.c=.d}

OBJS_LIBFT = ${LIBFT:.c=.o}
DEPS_LIBFT = ${LIBFT:.c=.d}

CC = gcc
FLAGS = -Wall -Wextra -Werror -MMD
RM = rm -f

SERVER = server
CLIENT = client
SERVER_BONUS = server_bonus
CLIENT_BONUS = client_bonus

all : $(LIBFT) $(SERVER) $(CLIENT)

-include ${DEPS_LIBFT} ${DEPS_SERV} ${DEPS_CL}

%.o : %.c Makefile
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

$(SERVER) : $(OBJS_LIBFT) $(OBJS_SERV)
	$(CC) $(FLAGS) $(OBJS_LIBFT) $(OBJS_SERV) -o $(SERVER)

$(CLIENT) : $(OBJS_LIBFT) $(OBJS_CL)
	$(CC) $(FLAGS) $(OBJS_LIBFT) $(OBJS_CL) -o $(CLIENT)

bonus : $(LIBFT) $(SERVER_BONUS) $(CLIENT_BONUS)

$(SERVER_BONUS) : $(OBJS_LIBFT) $(OBJS_SERV_BONUS)
	$(CC) $(FLAGS) $(OBJS_LIBFT) $(OBJS_SERV_BONUS) -o $(SERVER_BONUS)

$(CLIENT_BONUS) : $(OBJS_LIBFT) $(OBJS_CL_BONUS)
	$(CC) $(FLAGS) $(OBJS_LIBFT) $(OBJS_CL_BONUS) -o $(CLIENT_BONUS)

clean :
	$(RM) $(OBJS_SERV) $(OBJS_CL) $(OBJS_LIBFT) $(OBJS_SERV_BONUS) $(OBJS_CL_BONUS)
	$(RM) $(DEPS_SERV) $(DEPS_CL) $(DEPS_LIBFT) $(DEPS_SERV_BONUS) $(DEPS_CL_BONUS)

fclean : clean
	$(RM) $(SERVER) $(CLIENT)

bonus : $(LIBFT) $(SERVER_BONUS) $(CLIENT_BSERVER_BONUS)

re : fclean all

.PHONY: all clean fclean re
