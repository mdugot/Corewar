/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/21 15:05:02 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/02 19:21:29 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		new_champion_windows(t_viewer *v)
{
	int i;
	int x;
	int y;
	int w;
	int h;

	i = 0;
	w = 22;
	h = v->memory_h / 2;
	v->ch_w = w;
	v->ch_h = h;
	y = v->header_h;
	x = v->memory_w + v->info_w;
	while (i < MAX_PLAYERS)
	{
		v->champion[i] = new_window(x, y, w, h);
		if (i % 2)
		{
			y = v->header_h;
			x += v->ch_w;
		}
		else
			y = v->header_h + v->memory_h / 2;
		i++;
	}
}

t_viewer	*new_viewer(void)
{
	t_viewer	*v;

	v = ft_memalloc(sizeof(t_viewer));
	getmaxyx(stdscr, v->h, v->w);
	v->pause = 1;
	v->speed = 1;
	v->width_memory = 4;
	v->memory_line = 64;
	v->header_h = 15;
	v->memory_w = v->width_memory * v->memory_line + 2;
	v->memory_h = MEM_SIZE / v->memory_line + 2;
	v->memory = new_window(0, v->header_h, v->memory_w, v->memory_h);
	v->info_w = 40;
	v->info_h = v->memory_h;
	v->info = new_window(v->memory_w, v->header_h, v->info_w, v->info_h);
	new_champion_windows(v);
	v->header_w = v->memory_w + v->info_w + v->ch_w * 2;
	v->header = new_window(0, 0, v->header_w, v->header_h);
	init_opname(v->opname);
	init_color_pair();
	return (v);
}

void		first_screen(t_viewer *v)
{
	char tmp[200];

	attron(A_UNDERLINE | A_BOLD);
	ft_strcpy(tmp, "CONTROLS");
	mvprintw(v->h / 2 - 12, v->w / 2 - ft_strlen(tmp) / 2, tmp);
	attroff(A_UNDERLINE);
	ft_strcpy(tmp, "Q : quit");
	mvprintw(v->h / 2 - 8, v->w / 2 - ft_strlen(tmp) / 2, tmp);
	ft_strcpy(tmp, "SPACE : pause/unpause");
	mvprintw(v->h / 2 - 6, v->w / 2 - ft_strlen(tmp) / 2, tmp);
	ft_strcpy(tmp, "N : next turn");
	mvprintw(v->h / 2 - 4, v->w / 2 - ft_strlen(tmp) / 2, tmp);
	ft_strcpy(tmp, "TAB : display opname/display opcode");
	mvprintw(v->h / 2 - 2, v->w / 2 - ft_strlen(tmp) / 2, tmp);
	ft_strcpy(tmp, "UP : increase speed");
	mvprintw(v->h / 2, v->w / 2 - ft_strlen(tmp) / 2, tmp);
	ft_strcpy(tmp, "DOWN : decrease speed");
	mvprintw(v->h / 2 + 2, v->w / 2 - ft_strlen(tmp) / 2, tmp);
	ft_strcpy(tmp, "1 - 4 : display next process for player 1 to 4");
	mvprintw(v->h / 2 + 4, v->w / 2 - ft_strlen(tmp) / 2, tmp);
	attroff(A_BOLD);
	attron(A_REVERSE);
	ft_strcpy(tmp, "PRESS ANY KEY TO CONTINUE");
	mvprintw(v->h / 2 + 8, v->w / 2 - ft_strlen(tmp) / 2, tmp);
	attroff(A_REVERSE);
}

void		event(t_vm *vm, int ch)
{
	if (ch == '\t')
		vm->viewer->namemode = (vm->viewer->namemode ? 0 : 1);
	if (ch == ' ')
	{
		if (vm->viewer->pause)
			halfdelay(1);
		else
			cbreak();
		vm->viewer->pause = (vm->viewer->pause ? 0 : 1);
	}
	if (ch == KEY_UP)
		vm->viewer->speed += 1;
	if (ch == KEY_DOWN)
		vm->viewer->speed -= 1;
	if (vm->viewer->speed <= 0)
		vm->viewer->speed = 1;
	if (vm->viewer->speed > 100)
		vm->viewer->speed = 100;
	if (ch >= '1' && ch <= '4')
	{
		vm->viewer->actual_process[ch - '1'] += 1;
		if (vm->viewer->actual_process[ch - '1'] >= P[ch - '1'].pc_number)
			vm->viewer->actual_process[ch - '1'] = 0;
	}
}

int			update_visual(t_vm *vm)
{
	int	ch;

	draw_all(vm, vm->viewer);
	ch = 'a';
	while (ch != ERR && ch != ' ' && ch != 'n')
	{
		ch = getch();
		if (ch == 'q')
			return (1);
		event(vm, ch);
		if (ch != ERR)
			draw_all(vm, vm->viewer);
	}
	return (0);
}
