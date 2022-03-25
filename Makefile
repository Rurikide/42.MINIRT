NAME= miniRT
BNAME= miniRT_bonus

AR= ar rc
RM= rm -rf

CC= gcc
CFLAGS= -Wall -Wextra -Werror -c -g
MFLAGS= -Llibx -lmlx -framework OpenGL -framework Appkit

SDIR= srcs
ODIR= objs
ODIR_B = objs_bonus
ADIR= srcs/vector_array
CDIR= srcs/color
EDIR= srcs/event
MDIR= srcs/matrix
PDIR= srcs/parse
RDIR= srcs/ray_hit
SHDIR= srcs/shapes

#BONUS
SDIR_B = srcs_bonus
ADIR_B= srcs_bonus/vector_array_bonus
CDIR_B= srcs_bonus/color_bonus
EDIR_B= srcs_bonus/event_bonus
MDIR_B= srcs_bonus/matrix_bonus
PDIR_B= srcs_bonus/parse_bonus
RDIR_B= srcs_bonus/ray_hit_bonus
SHDIR_B= srcs_bonus/shapes_bonus


SRCS=	main.c
SRCS_B= main_bonus.c


ARRAY= vector_array.c vector_utils.c
COLOR= color.c color_rgb.c
EVENT= click_event.c event_cylinder.c event_plane.c event_sphere.c rotation.c translation_signal.c translation_work.c hook_utils.c minirt_utils.c terminate_utils.c
MATRIX= matrix_creation.c matrix_manipulation.c
PARSE= parse.c check_ambcamlit.c check_syntaxe.c check_valid_file.c parse_ambcamlit.c parse_rgb.c parse_settings.c parse_shape.c parse_utils.c parse_xyz.c
SHAPES= roots.c
RAY= get_color.c light.c ray.c

#BONUS
ARRAY_B= vector_array_bonus.c vector_utils_bonus.c
COLOR_B= color_bonus.c color_rgb_bonus.c
EVENT_B= click_event_bonus.c event_cylinder_bonus.c event_plane_bonus.c event_sphere_bonus.c rotation_bonus.c translation_signal_bonus.c translation_work_bonus.c hook_utils_bonus.c minirt_utils_bonus.c terminate_utils_bonus.c
MATRIX_B= matrix_creation_bonus.c matrix_manipulation_bonus.c
PARSE_B= parse_bonus.c check_ambcamlit_bonus.c check_syntaxe_bonus.c check_valid_file_bonus.c parse_ambcamlit_bonus.c parse_rgb_bonus.c parse_settings_bonus.c parse_shape_bonus.c parse_utils_bonus.c parse_xyz_bonus.c
SHAPES_B= roots_bonus.c
RAY_B= get_color_bonus.c light_bonus.c ray_bonus.c


OBJS= $(SRCS:.c=.o) $(ARRAY:.c=.o) $(COLOR:.c=.o) $(EVENT:.c=.o) $(MATRIX:.c=.o) $(PARSE:.c=.o) $(RAY:.c=.o) $(SHAPES:.c=.o) 

OBJS_B = $(SRCS_B:.c=.o) $(ARRAY_B:.c=.o) $(COLOR_B:.c=.o) $(EVENT_B:.c=.o) $(MATRIX_B:.c=.o) $(PARSE_B:.c=.o) $(RAY_B:.c=.o) $(SHAPES_B:.c=.o) 


SFIX= $(addprefix $(SDIR)/, $(SRCS))
OFIX= $(addprefix $(ODIR)/, $(OBJS)) 
AFIX= $(addprefix $(ADIR)/, $(ARRAY))
CFIX= $(addprefix $(CDIR)/, $(COLOR))
EFIX= $(addprefix $(EDIR)/, $(EVENT))
MFIX= $(addprefix $(MDIR)/, $(MATRIX))
PIX= $(addprefix $(PDIR)/, $(PARSE))
RFIX= $(addprefix $(RDIR)/, $(RAY)) 
SHFIX= $(addprefix $(SHDIR)/, $(SHAPES)) 

#BONUS
SFIX_B= $(addprefix $(SDIR_B)/, $(SRCS_B))
OFIX_B= $(addprefix $(ODIR_B)/, $(OBJS_B)) 
AFIX_B= $(addprefix $(ADIR_B)/, $(ARRAY_B))
CFIX_B= $(addprefix $(CDIR_B)/, $(COLOR_B))
EFIX_B= $(addprefix $(EDIR_B)/, $(EVENT_B))
MFIX_B= $(addprefix $(MDIR_B)/, $(MATRIX_B))
PIX_B= $(addprefix $(PDIR_B)/, $(PARSE_B))
RFIX_B= $(addprefix $(RDIR_B)/, $(RAY_B)) 
SHFIX_B= $(addprefix $(SHDIR_B)/, $(SHAPES_B)) 


VPATH= $(SDIR) $(ADIR) $(CDIR) $(EDIR) $(MDIR) $(PDIR) $(RDIR) $(SHDIR) $(SDIR_B) $(ADIR_B) $(CDIR_B) $(EDIR_B) $(MDIR_B) $(PDIR_B) $(RDIR_B) $(SHDIR_B)

$(NAME): $(ODIR) $(OFIX) 
	$(MAKE) -C ./libft
	$(MAKE) -C ./libx
	$(CC) $(OFIX) $(MFLAGS) -lft -L./libft -o $(NAME)
	@echo "\033[1;32mminiRT\033[0;39m"

$(ODIR)/%.o: %.c
	$(CC) $(CFLAGS) -I./libft/libsrcs -I./incls $< -o $@

$(ODIR_B)/%.o: %.c
	$(CC) $(CFLAGS) -I./libft/libsrcs -I./incls $< -o $@
	

$(ODIR):
		mkdir -p $(ODIR)

$(ODIR_B):
		mkdir -p $(ODIR_B)

all:	$(NAME)

bonus: $(BNAME)

$(BNAME): $(ODIR_B) $(OFIX_B) 
	$(MAKE) -C ./libft
	$(MAKE) -C ./libx
	$(CC) $(OFIX_B) $(MFLAGS) -lft -L./libft -o $(BNAME)

clean:
	$(MAKE) clean -C ./libft
	$(RM) $(NAME) $(BNAME) $(ODIR) $(ODIR_B)

fclean: clean
	$(MAKE) fclean -C ./libft
	@echo "\033[1;34m make fclean done!\033[0;39m"
	
re:	clean all








.PHONY: all clean flcean re bonus
