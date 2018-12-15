# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/24 15:12:04 by vomelchu          #+#    #+#              #
#    Updated: 2018/09/06 13:34:56 by vomelchu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lvl_editor

SRC_LVL_EDITOR = ./files/doom_nukem.c\
				./files/key.c ./files/bresenham.c ./files/for_list.c\
				./files/draw.c ./files/canvas.c ./files/writting.c\
				./files/crossing.c ./files/crossing_helper.c\
				./files/key_helper.c ./files/sdl.c\
				./files/writting_helper.c ./files/mouse_eve.c\
				./files/other.c ./files/menu.c ./files/object.c

OBJECT_LVL_EDITOR = $(SRC_LVL_EDITOR:.c=.o)

FLAGS = -Wall -Wextra

INCLUDES_LVL_EDITOR = -I ./includes/

INCLUDES_LIBFT = -I ./source/libft/includes

INCLUDES_SDL2 = -I ./source/SDL/SDL2.framework/Headers

INCLUDES_SDL2_IMAGE = -I ./source/SDL/SDL2_image.framework/Headers

INCLUDES_SDL2_MIXER = -I ./source/SDL/SDL2_mixer.framework/Headers

LIBFT = ./source/libft/libft.a

INCLUDES_SDL2_TTF = -I ./source/SDL/SDL2_ttf.framework/Headers

FRAMEWORK_SDL2 = -F ./source/SDL -framework SDL2 \
	-framework SDL2_image \
	-framework SDL2_ttf \
	-framework SDL2_mixer

FRAMEWORK_MLX = -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME) : $(OBJECT_LVL_EDITOR)
	make -C ./source/libft
	@echo "file: */lvl_editor"
	@gcc -g -fsanitize=address -o $(NAME) $(FLAGS) $(LIBFT) $(INCLUDES_SDL2) $(INCLUDES_SDL2_IMAGE) -rpath @loader_path/source/sdl $(FRAMEWORK_SDL2) $(OBJECT_LVL_EDITOR) $(INCLUDES_SDL2_TTF) $(INCLUDES_SDL2_MIXER)

%.o: %.c includes/*.h
	gcc -g $(FLAGS) -o $@ -c $< $(INCLUDES_LVL_EDITOR) $(INCLUDES_SDL2) $(INCLUDES_LIBFT) \
$(INCLUDES_SDL2_IMAGE) $(INCLUDES_SDL2_TTF) $(INCLUDES_SDL2_MIXER)

%.o: %.c
	gcc -g 	$(FLAGS) -o $@ -c $< $(INCLUDES_LVL_EDITOR) $(INCLUDES_SDL2) $(INCLUDES_LIBFT) \
$(INCLUDES_SDL2_IMAGE) $(INCLUDES_SDL2_TTF) $(INCLUDES_SDL2_MIXER)

	@echo "LVL_EDITOR compiled"
clean:
	make -C ./source/libft clean
	/bin/rm -f $(OBJECT_LVL_EDITOR)
	rm -f TAGS

fclean: clean
	/bin/rm -f ./source/libft/libft.a
	/bin/rm -f $(NAME)

re: fclean all tags

tags:
	etags -R *.c *.h
