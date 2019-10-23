# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbradama <lbradama@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/22 13:56:52 by gkessler          #+#    #+#              #
#    Updated: 2019/06/25 19:41:14 by lbradama         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	rt

SDIR			=	./src/
UI_DIR			=	./src/ui/
UIL_DIR			=	./src/ui/layouts/
PARS_DIR		=	./src/parser/
IDIR			=	./includes/
ODIR			=	./obj/

PARS_FILES 		=	scene.c \
					scene1.c \
					scene2.c \
					parser.c \
					parser1.c \
					parser2.c \
					parser3.c \
					parser4.c \
					parser5.c \
					parser6.c \
					pars_text.c \
					pars_text1.c \
					pars_text2.c

PARS_C_FILES		= $(addprefix $(PARS_DIR),$(PARS_FILES:.c=.o))
PARS_O_FILES		= $(addprefix $(ODIR),$(PARS_FILES:.c=.o))

UI_FILES		=	button.c \
					button1.c \
					button2.c \
					input.c \
					input2.c \
					input3.c \
					layout.c \
					general.c \
					structs.c \
					structs1.c \
					structs2.c

UI_C_FILES		=	$(addprefix $(UI_DIR),$(UI_FILES:.c=.o))
UI_O_FILES		=	$(addprefix $(ODIR),$(UI_FILES:.c=.o))


UIL_FILES		=	init.c \
					local1.c \
					local2.c \
					local3.c \
					local4.c \
					local5.c


UIL_C_FILES		=	$(addprefix $(UIL_DIR),$(UIL_FILES:.c=.o))
UIL_O_FILES		=	$(addprefix $(ODIR),$(UIL_FILES:.c=.o))

CFILES			=	main.c \
					main2.c \
					ui.c \
					canvas.c \
					canvas2.c \
					update_progress_bar.c \
					procedural_texture.c \
					put_pixel.c \
					color.c \
					filters.c \
					vec.c \
					vec1.c \
					vec2.c \
					vec3.c \
					vec4.c \
					gpu.c \
					gpu2.c \
					gpu3.c \
					random.c \
					free.c

OFILES			=	$(addprefix $(ODIR),$(CFILES:.c=.o))

CC				=	gcc
FLAGS			=	-g -Wall -Wextra -Werror
# FLAGS			=	-g

FT				=	./libft/
FT_LIB			=	$(addprefix $(FT),libft.a)
FT_INC			=	-I ./libft/includes
FT_LNK			=	-L ./libft -l ft


SDl_FW			=	includes/frameworks
SDL_INC			=	-I $(SDl_FW)/SDL2.framework/Versions/A/Headers \
					-I $(SDl_FW)/SDL2_image.framework/Versions/A/Headers \
					-I $(SDl_FW)/SDL2_ttf.framework/Versions/A/Headers \
					-F $(SDl_FW)

FRAM			=	-framework SDL2 -framework SDL2_image -framework SDL2_ttf -framework OpenCL

FRAMEWORKS		=	~/Library/Frameworks/SDL2.framework \
					~/Library/Frameworks/SDL2_image.framework \
					~/Library/Frameworks/SDL2_ttf.framework

all: obj $(FT_LIB) $(NAME)

obj:
	mkdir -p $(ODIR)

$(ODIR)%.o:$(UI_DIR)%.c
	gcc $(FLAGS) $(FT_INC) -I $(IDIR) $(SDL_INC) -o $@ -c $<

$(ODIR)%.o:$(UIL_DIR)%.c
	gcc $(FLAGS) $(FT_INC) -I $(IDIR) $(SDL_INC) -o $@ -c $<

$(ODIR)%.o:$(PARS_DIR)%.c
	gcc $(FLAGS) $(FT_INC) -I $(IDIR) $(SDL_INC) -o $@ -c $<

$(ODIR)%.o:$(SDIR)%.c
	gcc $(FLAGS) $(FT_INC) -I $(IDIR) $(SDL_INC) -o $@ -c $<

$(FT_LIB):
	make -C $(FT)

$(FRAMEWORKS):
	sh install.sh

$(NAME):  $(FRAMEWORKS) $(OFILES) $(UI_O_FILES) $(UIL_O_FILES) $(PARS_O_FILES)
	$(CC) $(FLAGS) $(OFILES) $(UI_O_FILES) $(UIL_O_FILES) $(PARS_O_FILES) $(FT_LNK)  -lm -F $(SDl_FW) $(FRAM) -o $(NAME)

clean:
	rm -rf $(ODIR)
	make -C $(FT) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(FT) fclean

re: fclean all

rrclean:
	rm -rf $(ODIR)
	rm -rf $(NAME)

rr: rrclean all