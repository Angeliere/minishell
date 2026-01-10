
NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
SRC_DIR = src
OBJ_DIR = obj
LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INC = -I$(LIBFT_DIR)
INCLUDES = -I. -I/usr/include $(LIBFT_INC)

SRCS =	minishell.c \
		command_lexer.c \
		lexer_utility.c \
		parser.c \

SRC_FILES = $(addprefix $(SRC_DIR)/, $(SRCS)) 
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

HEADERS = minishell.h

all:$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJS)
	@make -C $(LIBFT_DIR) clean
fclean: clean
	$(RM) $(NAME) 
	@make -C $(LIBFT_DIR) fclean
	
re: fclean all

.PHONY: all clean fclean re
