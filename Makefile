NAME := minishell
SRCS :=	main.c\
		shell/minishell.c shell/env.c shell/env_util.c\
		parser/heredoc.c parser/heredoc_util.c parser/tokenizer.c parser/syntax.c parser/compiler.c parser/unquote.c parser/unquote2.c parser/unquote3.c parser/process.c parser/process2.c\
		libft/allocate.c libft/copy.c libft/is_number.c libft/is_alphabet.c libft/ft_panic.c libft/printerr.c\
		str/str.c str/str2.c\
		collection/list.c collection/list_util.c\
		runner/execute.c runner/pipe_execute.c runner/util/complete_path.c runner/util/execute_util.c\
		signal/signal.c signal/signal2.c\
		runner/builtin/echo.c runner/builtin/pwd.c runner/builtin/exit.c runner/builtin/cd.c runner/builtin/export.c runner/builtin/export_sort.c runner/builtin/unset.c runner/builtin/env.c

OBJS := $(SRCS:%.c=%.o)
ARCS := 
LIBS := $(dir $(ARCS))
CFLAGS = -Wextra -Werror -Wall
READLINE_LINK = -L $(shell brew --prefix readline)/lib -lreadline
READLINE_COM = -I $(shell brew --prefix readline)/include

all: $(NAME)

$(NAME): $(ARCS) $(OBJS)
	$(CC) $(CFLAGS) $(READLINE_LINK) $(DEBUG) $(OBJS) $(ARCS) -o $(NAME) -I.

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) $(READLINE_COM) $(DEBUG) -c -o $@ $< -I.

$(ARCS):
	make -C $(@D) DEBUG="$(DEBUG)"

clean:
	rm -f $(OBJS)
	$(foreach dir, $(LIBS), make -C $(dir) clean;)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
