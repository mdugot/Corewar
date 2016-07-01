/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_visual.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 18:15:50 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/02 19:14:32 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

WINDOW		*new_window(int x, int y, int w, int h)
{
	WINDOW *new;

	new = newwin(h, w, y, x);
	wrefresh(new);
	return (new);
}

void		init_opname(char opname[16][5])
{
	ft_strcpy(opname[0], "LIVE");
	ft_strcpy(opname[1], " LD ");
	ft_strcpy(opname[2], " ST ");
	ft_strcpy(opname[3], "ADD ");
	ft_strcpy(opname[4], "SUB ");
	ft_strcpy(opname[5], "AND ");
	ft_strcpy(opname[6], " OR ");
	ft_strcpy(opname[7], "XOR ");
	ft_strcpy(opname[8], "ZJMP");
	ft_strcpy(opname[9], "LDI ");
	ft_strcpy(opname[10], "STI ");
	ft_strcpy(opname[11], "FORK");
	ft_strcpy(opname[12], "LLD ");
	ft_strcpy(opname[13], "LLDI");
	ft_strcpy(opname[14], "LFRK");
	ft_strcpy(opname[15], "AFF ");
}

void		init_color_champion(int color[MAX_PLAYERS])
{
	int	n;

	n = 0;
	while (n < MAX_PLAYERS)
	{
		color[n] = n % 4 + 8;
		n++;
	}
}

void		init_color_pair(void)
{
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_color(COLOR_BLUE, 0, 0, 200);
	init_color(COLOR_CYAN, 0, 700, 700);
	init_color(COLOR_WHITE, 600, 600, 600);
	init_pair(2, COLOR_CYAN, COLOR_BLUE);
	init_pair(3, COLOR_WHITE, COLOR_BLACK);
	init_pair(4, COLOR_WHITE, COLOR_BLUE);
	init_pair(5, COLOR_CYAN, COLOR_BLACK);
	init_pair(6, COLOR_BLACK, COLOR_BLUE);
	init_pair(7, COLOR_BLUE, COLOR_BLACK);
	init_pair(8, COLOR_RED, COLOR_BLACK);
	init_pair(9, COLOR_GREEN, COLOR_BLACK);
	init_pair(10, COLOR_YELLOW, COLOR_BLACK);
	init_pair(11, COLOR_MAGENTA, COLOR_BLACK);
}

void		init_visual(t_vm *vm)
{
	initscr();
	curs_set(0);
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	start_color();
	vm->viewer = new_viewer();
	init_color_champion(vm->viewer->champion_color);
	first_screen(vm->viewer);
	refresh();
	getch();
	draw_all(vm, vm->viewer);
}
