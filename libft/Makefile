NAME	=	libft.a

AR= ar rc
CC= gcc
CFLAGS= -Wall -Werror -Wextra -c -g
RLIB=	ranlib
RM= rm -rf

SDIR= libsrcs
ODIR= libobjs

SRCS	=	ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_memccpy.c \
			ft_memmove.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strlen.c \
			ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strncmp.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_strnstr.c \
			ft_atoi.c \
			ft_calloc.c \
			ft_strdup.c \
			ft_substr.c \
			ft_strdouble.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_split.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			get_next_line.c \
			get_next_line_utils.c \
			ft_printf.c \
			ft_category_is.c \
			ft_category_is2.c \
			ft_putcollection.c \
			ft_putcollection2.c \
			ft_power.c \
			ft_absolute.c \
			ft_free_table.c \
			ft_square_root.c \
			ft_atod.c \
			ft_isspace.c \
			ft_table_len.c \
			ft_is_space_tab.c \
			ft_skip_space_tab.c \
			ft_is_dash_comma_dot.c \




OBJS= $(SRCS:.c=.o)

SFIX= $(addprefix $(SDIR)/, $(SRCS))
OFIX= $(addprefix $(ODIR)/, $(OBJS)) 	


all: $(NAME)

$(NAME): $(ODIR) $(OFIX)
		$(AR) $(NAME) $(OFIX)
		$(RLIB) $(NAME)

$(ODIR):
	mkdir -p $(ODIR)

$(ODIR)/%.o: $(SDIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
		$(RM) $(OFIX) $(ODIR)

fclean: clean
				$(RM) $(NAME)
	
re: fclean all

.PHONY: all bonus clean fclean re
