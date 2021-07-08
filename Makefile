# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: julesvanderhoek <julesvanderhoek@studen      +#+                      #
#                                                    +#+                       #
#    Created: 2021/07/06 17:31:34 by julesvander   #+#    #+#                  #
#    Updated: 2021/07/08 14:35:09 by julesvander   ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo

OBJ_DIR = objs
SRC_DIR = srcs
_OBJ_FILES =	main \
				utils \
				init \
				philo

INC = includes/

_HEADERS = philo.h

HEADERS = $(addprefix $(INC),$(_HEADERS))

OBJ_FILES = $(addsuffix .o, $(addprefix $(OBJ_DIR)/,$(_OBJ_FILES)))

LIB = 

CFLAGS =

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)/$(dir $*)
	gcc -c $(CFLAGS) $< -o $@ -I$(INC)

$(NAME): $(OBJ_FILES)
	$(CC) -o $(NAME) $(OBJ_FILES) $(LIB) $(CFLAGS)

bonus:
	$(MAKE) WITH_BONUS=1 all

clean:
	/bin/rm -rf $(OBJ_DIR) main.o

fclean: clean
	/bin/rm -f $(NAME) execute

re: fclean all

.PHONY: all clean fclean re
