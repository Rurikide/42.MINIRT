NAME= miniRT

AR= ar rc
RM= rm -rf

CC= gcc
CFLAGS= -Wall -Wextra -c -g
MFLAGS= -Llibx -lmlx -framework OpenGL -framework Appkit

SDIR= srcs
ODIR= objs
ADIR= srcs/vector_array
CDIR= srcs/color
EDIR= srcs/event
PDIR= srcs/parse
RDIR= srcs/ray_hit
SHDIR= srcs/shapes
MDIR= srcs/mlx
VDIR= srcs/vector_3d

SRCS=	main.c


ARRAY= vector_array.c vector_utils.c
COLOR= color.c color_rgb.c
EVENT= move_cam.c matrix.c
PARSE= parse.c check_ambcamlit.c check_syntaxe.c check_valid_file.c parse_ambcamlit.c parse_rgb.c parse_settings.c parse_shape.c parse_utils.c parse_xyz.c
RAY= intersection.c get_color.c
SHAPES= sphere.c plane.c
MLX= mlx_utils.c scene_utils.c
VEC3D= vector_new.c vector_tool.c

OBJS= $(SRCS:.c=.o) $(ARRAY:.c=.o) $(COLOR:.c=.o) $(EVENT:.c=.o) $(PARSE:.c=.o) $(RAY:.c=.o) $(SHAPES:.c=.o) $(MLX:.c=.o) $(VEC3D:.c=.o)


SFIX= $(addprefix $(SDIR)/, $(SRCS))
OFIX= $(addprefix $(ODIR)/, $(OBJS)) 
AFIX= $(addprefix $(ADIR)/, $(ARRAY))
CFIX= $(addprefix $(CDIR)/, $(COLOR))
EFIX= $(addprefix $(EDIR)/, $(EVENT)) 
PIX= $(addprefix $(PDIR)/, $(PARSE))
RFIX= $(addprefix $(RDIR)/, $(RAY)) 
SHFIX= $(addprefix $(SHDIR)/, $(SHAPES)) 
MFIX= $(addprefix $(MDIR)/, $(MLX)) 
VFIX= $(addprefix $(VDIR)/, $(VEC3D))

VPATH= $(SDIR) $(ADIR) $(CDIR) $(EDIR) $(PDIR) $(RDIR) $(SHDIR) $(MDIR) $(VDIR)

$(NAME): $(ODIR) $(OFIX) 
	$(MAKE) -C ./libft
	$(MAKE) -C ./libx
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
