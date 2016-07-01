# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdugot <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/03 12:08:51 by mdugot            #+#    #+#              #
#    Updated: 2016/06/06 11:51:30 by mdugot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= asm
CC= gcc
CFLAGS= -Wall -Werror -Wextra
SRC_NAME= read_it.c endian.c instruct_lst.c read_instru.c instruct_lst_aj.c verif_instru.c error.c convert.c verif_param.c write_byte_code.c nasm.c encode.c ft_instru.c
SRC_PATH= ./sources/
INC_PATH= ./includes/
LIB_NAME= libftprintf.a
LIB_ID= ftprintf
LIB_PATH= ./libft/
LIB_INC= ./libft/
OBJ_NAME= $(SRC_NAME:.c=.o)
OBJ_PATH= ./obj/
SRC= $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ= $(addprefix $(OBJ_PATH), $(OBJ_NAME))
LIB= $(addprefix $(LIB_PATH), $(LIB_NAME))

.PHONY: all
all: $(NAME)
	
$(NAME): $(LIB) $(OBJ)
	$(CC) $(CFLAGS)  -L$(LIB_PATH) -I$(INC_PATH) -o $(NAME) -l$(LIB_ID) $(OBJ)

$(LIB):
	make re -C $(LIB_PATH)

.PHONY: libft
libft:
	make re -C $(LIB_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	$(CC) -I$(INC_PATH) -I$(LIB_INC) $(CFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	rm -fv $(OBJ)
	@rm -rf $(OBJ_PATH)
	make $@ -C $(LIB_PATH)

.PHONY: fclean
fclean: clean
	rm -fv $(NAME)
	make $@ -C $(LIB_PATH)

.PHONY: re
re: fclean all
