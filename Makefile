# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbadia <jbadia@student.42quebec.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/06 15:46:15 by tshimoda          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2022/02/16 15:17:14 by jbadia           ###   ########.fr        #
=======
#    Updated: 2022/02/16 15:09:47 by tshimoda         ###   ########.fr        #
>>>>>>> master
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
#CDIR= srcs/color
PDIR= srcs/parse
VDIR= srcs/vector_3d
ODIR= objs

<<<<<<< HEAD
SRCS=	main.c color.c init.c mlx_utils.c 
=======
SRCS= main.c
>>>>>>> master
ARRAY= vector_array.c vector_utils.c
#COLOR= color.c
PARSE= parse.c
VEC3D= vector_new.c vector_tool.c

OBJS= $(SRCS:.c=.o) $(ARRAY:.c=.o) $(VEC3D:.c=.o)

SFIX= $(addprefix $(SDIR)/, $(SRCS))
AFIX= $(addprefix $(ADIR)/, $(ARRAY))
#CFIX= $(addprefix $(CDIR)/, $(COLOR))
PIX= $(addprefix $(PDIR)/, $(PARSE))
VFIX= $(addprefix $(VDIR)/, $(VEC3D))
OFIX= $(addprefix $(ODIR)/, $(OBJS)) 

VPATH= $(SDIR) $(ADIR) $(PDIR) $(VDIR) #$(CDIR)

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
