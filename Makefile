# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbadia <jbadia@student.42quebec.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/06 15:46:15 by tshimoda          #+#    #+#              #
#    Updated: 2022/02/20 18:21:42 by jbadia           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= miniRT

AR= ar rc
RM= rm -rf

CC= gcc
CFLAGS= -Wall -Wextra -c -g
MFLAGS= -Lminilibx_opengl -lmlx -framework OpenGL -framework Appkit

SDIR= srcs
ADIR= srcs/vector_array
CDIR= srcs/color
PDIR= srcs/parse
VDIR= srcs/vector_3d
SHDIR = srcs/shapes
RDIR = srcs/ray_hit
ODIR= objs

SRCS=	main.c init.c mlx_utils.c 
ARRAY= vector_array.c vector_utils.c
PARSE= parse.c
COLOR= color.c
VEC3D= vector_new.c vector_tool.c
SHAPES= sphere.c
RAY = intersection.c

OBJS= $(SRCS:.c=.o) $(ARRAY:.c=.o) $(VEC3D:.c=.o) $(COLOR:.c=.o) $(SHAPES:.c=.o) $(RAY:.c=.o)

SFIX= $(addprefix $(SDIR)/, $(SRCS))
AFIX= $(addprefix $(ADIR)/, $(ARRAY))
CFIX= $(addprefix $(CDIR)/, $(COLOR))
PIX= $(addprefix $(PDIR)/, $(PARSE))
VFIX= $(addprefix $(VDIR)/, $(VEC3D))
OFIX= $(addprefix $(ODIR)/, $(OBJS)) 
SHFIX= $(addprefix $(SHDIR)/, $(SHAPES)) 
RFIX= $(addprefix $(RDIR)/, $(RAY)) 

VPATH= $(SDIR) $(ADIR) $(PDIR) $(VDIR) $(CDIR) $(SHDIR) $(RDIR)

$(NAME): $(ODIR) $(OFIX) 
	$(MAKE) -C ./libft
	$(MAKE) -C ./minilibx_opengl
	$(CC) $(OFIX) $(MFLAGS) -lft -L./libft -o $(NAME)
	@echo "\033[1;32mminiRT\033[0;39m"

$(ODIR)/%.o: %.c
	$(CC) $(CFLAGS) -I./libft/libsrcs -I./incls $< -o $@
	
all:	$(NAME)

$(ODIR):
		mkdir -p $(ODIR)

clean:
	$(MAKE) clean -C ./libft
	$(RM) $(NAME) $(ODIR)

fclean: clean
	$(MAKE) fclean -C ./libft
	@echo "\033[1;34m make fclean done!\033[0;39m"
	
re:	clean all

.PHONY: all clean flcean re
