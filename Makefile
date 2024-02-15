NAME=cub3d
SRC = src/main.c src/parcing.c ./get_next_line.c ./get_next_line_utils.c src/parc_utils.c src/utils.c src/textures.c src/colors.c src/utils_1.c src/window.c src/to_int.c
HEADER=philo.h
OBJ=$(SRC:src/%.c=obj/%.o)
CC= cc 
FRAME_FLAGS = -lmlx -framework OpenGl -framework AppKit
G_FLAG = -Imlx
LIBFT=libft/libft.a
CFLAGS=-Wall -Werror -Wextra
RM=rm -rf

all: libcomp creat_dir $(NAME) $(OBJ) Makefile

libcomp:
	@make -C libft

creat_dir:
	mkdir -p obj

obj/%.o : src/%.c
	$(CC) $(CFLAGS) $(G_FLAG) -c $< -o $@

$(NAME) : $(OBJ) Makefile
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(FRAME_FLAGS) -o $(NAME)

clean:
	@make -C libft clean
	$(RM) obj

fclean: clean
	$(RM) $(NAME)
	@make -C libft fclean

re: fclean all

.PHONY: re readline fclean clean all