NAME := minishell
SRCS := main.c str.c tokenizer.c allocate.c list.c syntax.c heredoc.c copy.c parser.c is_number.c is_alphabet.c minishell.c
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