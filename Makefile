CC = cc
CFLAG = -Wall -Wextra -Werror
NAME = fdf
LIBFT_DIR = ./libft/
LIBFT_NAME = libft.a
SRCS = fdf_main.c fdf_parsing.c fdf_bresenham.c fdf_draw_map.c 
OBJS = $(SRCS:.c=.o)
MLXDIR = ./minilibx_mms_20210621
MLXFLAG = -L $(MLXDIR) -lmlx -L $(LIBFT_DIR) -lft -framework OpenGL -framework AppKit
LIBMLXDIR = ./minilibx_mms_20210621

.PHONY: all

all: $(NAME)

$(NAME): $(OBJS) fdf.h
	make -s -C $(LIBFT_DIR)
	make -s -C $(MLXDIR)
	cp ./$(MLXDIR)/libmlx.dylib ./libmlx.dylib
	$(CC) $(CFLAG) $(OBJS) $(MLXFLAG) -o $(NAME)

$(OBJS)	: $(SRCS) 
	$(CC) $(CFLAG) -c $^

clean:
	make -C $(LIBFT_DIR) clean
	make -C $(MLXDIR) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	rm -f libmlx.dylib

re: fclean all

.PHONY: all clean fclean re
