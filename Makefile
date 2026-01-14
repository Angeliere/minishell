NAME        := minishell

CC          := cc
CFLAGS      := -Wall -Wextra -Werror
RM          := rm -f

OBJ_DIR     := obj
LIBFT_DIR   := libft
LIBFT       := $(LIBFT_DIR)/libft.a

SRCS        :=	minishell.c \
				minishell_main_util.c \
            	lexer.c \
            	lexer_utility.c \
				lexer_var.c \
				lexer_add.c \
				lexer_word.c \
            	parser.c \
				parser_utils.c \
				parser_quotes.c \
				parser_syntax_check.c \
				parser_add.c \
				parser_redir.c \
				parser_argv.c \
				expand_var.c \
				expand_var_utils.c \
				env_utils.c \
				env_utils2.c \
				env_manage.c \
				builtins_dispatcher.c \
				builtins_echo.c \
				builtins_pwd.c \
				builtins_cd.c \
				builtins_env.c \
				builtins_exit.c \
				builtins_export.c \
				builtins_unset.c \
				exec_utils.c \
				exec_str_manip.c \
				exec_cmd_utils.c \
				exec.c

OBJS        := $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

INCLUDES    := -I. -I$(LIBFT_DIR)/include

# ===================================================== #
# OS detection
# ===================================================== #
UNAME := $(shell uname)

ifeq ($(UNAME),Darwin)
	READLINE_INC := -I$(shell brew --prefix readline)/include
	READLINE_LIB := -L$(shell brew --prefix readline)/lib
	READLINE_LNK := -lreadline -lhistory -lncurses
else
	READLINE_INC :=
	READLINE_LIB :=
	READLINE_LNK := -lreadline
endif

CFLAGS  += $(READLINE_INC)
LDFLAGS := $(READLINE_LIB)
LDLIBS  := $(LIBFT) $(READLINE_LNK)

# ===================================================== #

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c minishell.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	$(RM) -r $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
