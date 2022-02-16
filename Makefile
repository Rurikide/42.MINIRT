# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/06 15:46:15 by tshimoda          #+#    #+#              #
#    Updated: 2022/02/15 21:08:19 by tshimoda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= miniRT

AR= ar rc
RM= rm -rf

CC= gcc
CFLAGS= -Wall -Wextra -c -g
MFLAGS= -Lminilibx_opengl -lmlx -framework OpenGL -framework Appkit

SDIR= srcs
ODIR= objs

SRCS=	main_test_jour_3.c \

OBJS= $(SRCS:.c=.o)

SFIX= $(addprefix $(SDIR)/, $(SRCS))
OFIX= $(addprefix $(ODIR)/, $(OBJS)) 

VPATH= $(SDIR)

$(ODIR)/%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

$(NAME): $(ODIR) $(OFIX)
	$(MAKE) -C ./libft
	$(MAKE) -C ./minilibx_opengl
	$(CC) $(OFIX) $(MFLAGS) -lft -L./libft -o $(NAME)
	$(CC) $(OFIX) $(MFLAGS) -o $(NAME)
	@echo "\033[1;32mminiRT\033[0;39m"

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
