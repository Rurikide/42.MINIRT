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
MDIR = srcs/movements
ODIR= objs

SRCS=	main.c init.c mlx_utils.c 


ARRAY= vector_array.c vector_utils.c
COLOR= color.c color_rgb.c
PARSE= parse.c parse_ambiant.c parse_camera.c parse_len.c parse_light.c parse_shape.c parse_utils.c 
VEC3D= vector_new.c vector_tool.c
SHAPES= sphere.c
RAY = intersection.c get_color.c
MOV = move_cam.c

OBJS= $(SRCS:.c=.o) $(ARRAY:.c=.o) $(VEC3D:.c=.o) $(COLOR:.c=.o) $(SHAPES:.c=.o) $(RAY:.c=.o) $(PARSE:.c=.o) $(MOV:.c=.o)


SFIX= $(addprefix $(SDIR)/, $(SRCS))
AFIX= $(addprefix $(ADIR)/, $(ARRAY))
CFIX= $(addprefix $(CDIR)/, $(COLOR))
PIX= $(addprefix $(PDIR)/, $(PARSE))
VFIX= $(addprefix $(VDIR)/, $(VEC3D))
OFIX= $(addprefix $(ODIR)/, $(OBJS)) 
SHFIX= $(addprefix $(SHDIR)/, $(SHAPES)) 
RFIX= $(addprefix $(RDIR)/, $(RAY)) 
MFIX = $(addprefix $(MDIR)/, $(MOV)) 

VPATH= $(SDIR) $(ADIR) $(PDIR) $(VDIR) $(CDIR) $(SHDIR) $(RDIR) $(MDIR)

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
