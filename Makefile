GCC := gcc -Wall -Wextra -Werror
CLIENT := client
SERVER := server
CLIENT_SRC := ./srcs/client/client.c
SERVER_SRC := ./srcs/server/server.c
CLIENT_OBJ := $(CLIENT_SRC:.c=.o)
SERVER_OBJ := $(SERVER_SRC:.c=.o)
LIBFT := libft/libft.a

all: $(LIBFT) $(CLIENT) $(SERVER)

$(LIBFT):
	@$(MAKE) -C libft all

$(CLIENT): $(CLIENT_OBJ)
		$(GCC) -o $(CLIENT) $(CLIENT_OBJ) $(LIBFT)

$(SERVER): $(SERVER_OBJ)
		$(GCC) -o $(SERVER) $(SERVER_OBJ) $(LIBFT)

%.o: %.c
		$(GCC) -o $@ -c $<

clean:
		@$(MAKE) -C libft clean
		rm -f $(SERVER_OBJ) $(CLIENT_OBJ)

fclean:
		@$(MAKE) -C libft fclean
		rm -f $(CLIENT) $(SERVER) $(CLIENT_OBJ) $(SERVER_OBJ)

re: fclean all