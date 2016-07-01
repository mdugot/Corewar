# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdugot <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/03 12:08:51 by mdugot            #+#    #+#              #
#    Updated: 2016/06/06 11:48:26 by mdugot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= corewar
CC= gcc
CFLAGS= -Wall -Werror -Wextra
SRC_NAME= main.c read_champion.c endian.c champion.c dispatch.c vm.c \
		  f_add.c f_sub.c f_ld.c f_lld.c f_st.c f_and.c f_or.c f_xor.c \
		  f_aff.c f_sti.c f_ldi.c f_lldi.c f_zjmp.c f_live.c f_fork.c \
		  check_reg.c cast_in.c convert.c \
		  instruction.c verification.c visual.c visual_tools.c draw.c \
		  find_champion.c utils.c draw_utils.c init.c init_visual.c
SRC_PATH= ./sources/
INC_PATH= ./includes/
LIB_NAME= libft.a
LIB_ID= ft
LIB_PATH= ./libft/
LIB_INC= ./libft/includes/
OBJ_NAME= $(SRC_NAME:.c=.o)
OBJ_PATH= ./obj/
SRC= $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ= $(addprefix $(OBJ_PATH), $(OBJ_NAME))
LIB= $(addprefix $(LIB_PATH), $(LIB_NAME))

.PHONY: all
all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	$(CC) $(CFLAGS)  -L$(LIB_PATH) -I$(INC_PATH) -o $(NAME) -l$(LIB_ID) -lncurses $(OBJ)

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
