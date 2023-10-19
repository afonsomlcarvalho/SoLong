NAME = so_long

COMPILER = cc -Wall -Werror -Wextra

SRCS = bonus_utils.c \
		display.c \
		enemy.c \
		finish.c \
		free.c \
		map_creator.c \
		object.c \
		so_long.c \
		utils.c \
		weapon.c

SRCSPR = ft_nbrlen.c \
		ft_printf.c \
		ft_putnbrs.c

SRCSLIB = ft_itoa.c \
			ft_putchar_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			ft_split.c \
			ft_strdup.c \
			ft_strlen.c

SRCSGNL = get_next_line.c \
			get_next_line_utils.c

SRCSLIBF = $(addprefix libft/, $(SRCSLIB))
SRCSPRF = $(addprefix printf/, $(SRCSPR))
SRCSGNLF = $(addprefix getnextline/, $(SRCSGNL))

OBJS = $(SRCS:.c=.o)
OBJSLIB = $(SRCSLIBF:.c=.o)
OBJSPR = $(SRCSPRF:.c=.o)
OBJSGNL = $(SRCSGNLF:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(OBJSLIB) $(OBJSPR) $(OBJSGNL)
	@$(COMPILER) $(OBJS) $(OBJSLIB) $(OBJSPR) $(OBJSGNL) -Lmlx_linux1 -lmlx_Linux -L/usr/lib -Imlx_linux1 -lXext -lX11 -lm -lz -o so_long

clean:
	@rm -f *.o libft/*.o printf/*.o getnextline/*.o

fclean: clean
	@rm -f so_long

re: fclean all
