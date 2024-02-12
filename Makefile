SRC_SERV = server.c
SRC_CL = client.c

LIBFT_DIR = ./libft/
LIBFT = ./libft/libft.a

HS = minitalk.h $(LIBFT)

OBJS_SERV = ${SRC_SERV:.c=.o}
DEPS_SERV = ${SRC_SERV:.c=.d}

OBJS_CL = ${SRC_CL:.c=.o}
DEPS_CL = ${SRC_CL:.c=.d}

CC = gcc
FLAGS = -Wall -Wextra -Werror -MMD
RM = rm -f

SERVER = server
CLIENT = client

all : $(LIBFT) $(SERVER) $(CLIENT)

-include ${DEPS_SERV} ${DEPS_CL}

%.o : %.c Makefile
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

$(SERVER) : $(OBJS_SERV)
	$(CC) $(FLAGS) $(LIBFT) $(OBJS_SERV) -o $(SERVER)

$(CLIENT) : $(OBJS_CL)
	$(CC) $(FLAGS) $(LIBFT) $(OBJS_CL) -o $(CLIENT)

$(LIBFT) :
	make -C $(LIBFT_DIR)

clean :
	make clean -C $(LIBFT_DIR)
	$(RM) $(OBJS_SERV) $(OBJS_CL) $(DEPS_SERV) $(DEPS_CL)

fclean : clean
	make fclean -C $(LIBFT_DIR)
	$(RM) $(SERVER) $(CLIENT)

re : fclean all

.PHONY: all clean fclean re
