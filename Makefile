FLAGS = -Wall -Wextra -Werror
CLIENT = client
SERVER = server

%: %.c
	gcc $(FLAGS) $@.c -o $@

all: $(CLIENT) $(SERVER)

clean:

fclean: clean
	rm -rf $(CLIENT) $(SERVER)

re: fclean all

.PHONY: all clean fclean re
