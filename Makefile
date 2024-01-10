NAME = ft_ls
LIB_NAME = libft.a

HEADER = ./inc/ft_ls.h
LIB_PATH = ./libft/
LST_SRCS =  main.c \
			utils.c \
			dir_infos.c \
			mem_utils.c \
			print_utils.c \
			print.c \
			struct_utils.c \
			parser.c \
			lst_utils.c \
			sort.c \
			dir_parse.c \
			arg_list_utils.c \
			dup.c \
			dir_parse_utils.c

LST_OBJS = $(LST_SRCS:.c=.o)

CC = gcc
FLAGS = -Wextra -Werror -Wall
RM = rm -rf

DIR_FILES = srcs
DIR_OBJS = .objs

LST	= 

SRCS = $(addprefix $(DIR_FILES)/,$(LST_SRCS))
OBJS = $(addprefix $(DIR_OBJS)/,$(LST_OBJS))

all : libft $(NAME)

$(DIR_OBJS)/%.o : $(DIR_FILES)/%.c $(HEADER) $(LIB_PATH)$(LIB_NAME)
	@mkdir -p $(DIR_OBJS) $(addprefix $(DIR_OBJS)/,$(LST))
	$(CC) -c $(FLAGS) -I ./inc/ -I $(LIB_PATH) $< -o $@

$(NAME) : $(LIB_PATH)$(LIB_NAME) $(OBJS) $(HEADER)
		@gcc $(FLAGS) $(OBJS) -I ./inc/ -I $(LIB_PATH) -L libft/ -lft -o $(NAME)

libft :
		make -C $(LIB_PATH)

$(LIB_PATH)$(LIB_NAME) : libft

clean :
		$(RM) $(DIR_OBJS)
		make clean -C $(LIB_PATH)

fclean : clean
	$(RM) $(NAME)
	make fclean -C $(LIB_PATH)

re : fclean all

.PHONY : clean fclean re all libft