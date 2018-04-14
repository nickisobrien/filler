NAME = nobrien.filler

SRC = srcs/main.c srcs/algorithm.c srcs/debugger.c srcs/init.c srcs/piece_handling.c srcs/reader.c srcs/o_overlaps.c

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
