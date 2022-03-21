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
MDIR= srcs/matrix
PDIR= srcs/parse
RDIR= srcs/ray_hit
SHDIR= srcs/shapes
VDIR= srcs/vector_3d

SRCS=	main.c


ARRAY= vector_array.c vector_utils.c
COLOR= color.c color_rgb.c
EVENT= click_event.c event_cylinder.c event_plane.c event_sphere.c rotation.c translation_signal.c translation_work.c hook_utils.c minirt_utils.c terminate_utils.c
MATRIX= matrix_creation.c matrix_manipulation.c
PARSE= parse.c check_ambcamlit.c check_syntaxe.c check_valid_file.c parse_ambcamlit.c parse_rgb.c parse_settings.c parse_shape.c parse_utils.c parse_xyz.c
RAY= ray.c intersection.c get_color.c
SHAPES= sphere.c plane.c
RAY = get_color.c light.c
VEC3D= vector_new.c vector_tool.c

OBJS= $(SRCS:.c=.o) $(ARRAY:.c=.o) $(COLOR:.c=.o) $(EVENT:.c=.o) $(MATRIX:.c=.o) $(PARSE:.c=.o) $(RAY:.c=.o) $(SHAPES:.c=.o) $(VEC3D:.c=.o)


SFIX= $(addprefix $(SDIR)/, $(SRCS))
OFIX= $(addprefix $(ODIR)/, $(OBJS)) 
AFIX= $(addprefix $(ADIR)/, $(ARRAY))
CFIX= $(addprefix $(CDIR)/, $(COLOR))
EFIX= $(addprefix $(EDIR)/, $(EVENT))
MFIX= $(addprefix $(MDIR)/, $(MATRIX))
PIX= $(addprefix $(PDIR)/, $(PARSE))
RFIX= $(addprefix $(RDIR)/, $(RAY)) 
SHFIX= $(addprefix $(SHDIR)/, $(SHAPES)) 
VFIX= $(addprefix $(VDIR)/, $(VEC3D))

VPATH= $(SDIR) $(ADIR) $(CDIR) $(EDIR) $(MDIR) $(PDIR) $(RDIR) $(SHDIR) $(VDIR)

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
