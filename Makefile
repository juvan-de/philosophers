# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: abelfranciscusvanbergen <abelfranciscus      +#+                      #
#                                                    +#+                       #
#    Created: 2020/12/15 14:09:10 by abelfrancis   #+#    #+#                  #
#    Updated: 2021/01/27 16:20:04 by julesvander   ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell

OBJ_DIR = objs
SRC_DIR = srcs
_OBJ_FILES = main \
			parsing/tokenizer \
			parsing/parser \
			parsing/distribution \
			pipes/pipe \
			parsing/expanding/expand \
			parsing/expanding/insert_var \
			redirects/redirection \
			utils/utils1 \
			utils/pipes \
			utils/free \
			utils/list \
			utils/other_cmds \
			utils/exit \
			utils/envvar \
			utils/str_allocating \
			utils/array_allocating \
			utils/str \
			utils/array \
			envvar/envvar_init \
			envvar/envvar_add \
			export/export \
			env/env \
			echo/echo \
			pwd/pwd \
			cd/cd \
			exit/exit \
			unset/unset \
			signals/signals \
			cmds/other_cmds

INC = includes/

_HEADERS = minishell.h minishell_prototypes.h minishell_types.h distributor.h

HEADERS = $(addprefix $(INC),$(_HEADERS))

OBJ_FILES = $(addsuffix .o, $(addprefix $(OBJ_DIR)/,$(_OBJ_FILES)))

LIB = -L./libft -lft -L./ft_printf -lftprintf  -L./getnextline -lgnl

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)/$(dir $*)
	gcc -c $(CFLAGS) $< -o $@ -I$(INC)

$(NAME): $(OBJ_FILES)
	make bonus -C libft
	make -C ft_printf
	make -C getnextline
	$(CC) -o $(NAME) $(OBJ_FILES) $(LIB) $(CFLAGS)

bonus:
	$(MAKE) WITH_BONUS=1 all

clean:
	/bin/rm -rf $(OBJ_DIR) main.o
	$(MAKE) -C libft clean
	$(MAKE) -C ft_printf clean
	$(MAKE) -C getnextline clean

fclean: clean
	$(MAKE) -C libft fclean
	$(MAKE) -C ft_printf fclean
	$(MAKE) -C getnextline fclean
	/bin/rm -f $(NAME) execute
	/bin/rm -f libft/libft.a
	/bin/rm -f libft.a
	/bin/rm -f ft_printf/libftprintf.a
	/bin/rm -f libftprintf.a
	/bin/rm -f getnextline/libgnl.a
	/bin/rm -f libgnl.a

re: fclean all

.PHONY: all clean fclean re
