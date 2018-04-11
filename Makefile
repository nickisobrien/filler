NAME = nobrien.filler

SRC = srcs/main.c

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(SRC)
	@make -C ./libft all
	gcc $(FLAGS) -o $(NAME) $(SRC) libft/libft.a

clean:
	@make -C ./libft clean

fclean: clean
	rm -f ./libft/libft.a
	rm -f $(NAME)

re: fclean all
