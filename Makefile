CC := gcc
CFLAGS := -Wall -Wextra -Werror -D_XOPEN_SOURCE=700 -D_DEFAULT_SOURCE
CLIENT := client
SERVER := server
CLIENT_SRC := ./srcs/client/client.c
SERVER_SRC := ./srcs/server/server.c ./srcs/server/server_utils.c
CLIENT_OBJ := $(CLIENT_SRC:.c=.o)
SERVER_OBJ := $(SERVER_SRC:.c=.o)
LIBFT := libft/libft.a

all: $(LIBFT) $(CLIENT) $(SERVER)

$(LIBFT):
	@$(MAKE) -C libft all

$(CLIENT): $(CLIENT_OBJ)
	$(CC) $(CFLAGS) -o $(CLIENT) $(CLIENT_OBJ) $(LIBFT)

$(SERVER): $(SERVER_OBJ)
	$(CC) $(CFLAGS) -o $(SERVER) $(SERVER_OBJ) $(LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@$(MAKE) -C libft clean
	rm -f $(SERVER_OBJ) $(CLIENT_OBJ)

fclean:
	@$(MAKE) -C libft fclean
	rm -f $(CLIENT) $(SERVER) $(CLIENT_OBJ) $(SERVER_OBJ)

re: fclean all

.PHONY: all clean fclean re