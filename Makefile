# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/06 15:46:15 by tshimoda          #+#    #+#              #
#    Updated: 2022/02/16 12:38:17 by tshimoda         ###   ########.fr        #
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

ODIR= objs

SRCS=	main.c
ARRAY= vector_array.c vector_utils.c

OBJS= $(SRCS:.c=.o) $(ARRAY:.c=.o)

SFIX= $(addprefix $(SDIR)/, $(SRCS))
AFIX= $(addprefix $(ADIR)/, $(ARRAY))
OFIX= $(addprefix $(ODIR)/, $(OBJS)) 

VPATH= $(SDIR) $(ADIR)

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
