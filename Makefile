# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdugot <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/03 12:08:51 by mdugot            #+#    #+#              #
#    Updated: 2016/06/06 11:56:31 by cdrouet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all
all:
	make -C ./asm
	make -C ./vm

.PHONY: libft
libft:
	make libft -C ./asm
	make libft -C ./vm

.PHONY: clean
clean:
	make clean -C ./asm
	make clean -C ./vm

.PHONY: fclean
fclean:
	make fclean -C ./asm
	make fclean -C ./vm

.PHONY: re
re:
	make re -C ./asm
	make re -C ./vm
