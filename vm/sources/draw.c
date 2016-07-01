/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/21 17:24:20 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/05 15:42:08 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#define H1A "    ,o888888o.        ,o888888o.     8 888888888o.   8 8888888888 "
#define H2A "   8888     `88.   . 8888     `88.   8 8888    `88.  8 8888       "
#define H3A ",8 8888       `8. ,8 8888       `8b  8 8888     `88  8 8888       "
#define H4A "88 8888           88 8888        `8b 8 8888     ,88  8 8888       "
#define H5A "88 8888           88 8888         88 8 8888.   ,88'  8 88888888888"
#define H6A "88 8888           88 8888         88 8 888888888P'   8 8888       "
#define H7A "88 8888           88 8888        ,8P 8 8888`8b       8 8888       "
#define H8A "`8 8888       .8' `8 8888       ,8P  8 8888 `8b.     8 8888       "
#define H9A "   8888     ,88'   ` 8888     ,88'   8 8888   `8b.   8 8888       "
#define H10A "    `8888888P'        `8888888P'     8 8888     `88. 8 8888888888"

#define H1B "`8.`888b                 ,8' .8.          8 888888888o.   "
#define H2B " `8.`888b               ,8' .888.         8 8888    `88.  "
#define H3B "  `8.`888b             ,8' :88888.        8 8888     `88  "
#define H4B "   `8.`888b     .b    ,8' . `88888.       8 8888     ,88  "
#define H5B "8   `8.`888b    88b  ,8' .8. `88888.      8 8888.   ,88'  "
#define H6B "     `8.`888b .`888b,8' .8`8. `88888.     8 888888888P'   "
#define H7B "      `8.`888b8.`8888' .8' `8. `88888.    8 8888`8b       "
#define H8B "       `8.`888`8.`88' .8'   `8. `88888.   8 8888 `8b.     "
#define H9B "        `8.`8' `8,`' .888888888. `88888.  8 8888   `8b.   "
#define H10B "88        `8.`   `8' .8'       `8. `88888. 8 8888     `88. "

void	draw_memory(t_vm *vm, t_viewer *v, WINDOW *w)
{
	int i;
	int x;
	int y;
	int color;
	int mem;

	i = 0;
	while (i < MEM_SIZE)
	{
		y = i / v->memory_line + 1;
		x = (i % v->memory_line) * v->width_memory + 1;
		color = find_mem_color(vm, v, i, y);
		wattron(w, COLOR_PAIR(color));
		mem = vm->memory[i];
		if (mem >= 1 && mem <= 16 && v->namemode)
		{
			wattron(w, A_REVERSE);
			mvwprintw(w, y, x, "%*s", v->width_memory, v->opname[mem - 1]);
		}
		else
			mvwprintw(w, y, x, " %0*hhx ", v->width_memory - 2, vm->memory[i]);
		i++;
		wattroff(w, A_REVERSE);
	}
	refresh_window(w);
}

void	draw_info(t_vm *vm, t_viewer *v, WINDOW *w)
{
	int l;

	l = 10;
	print_middle_str(w, "*** MODE ***", v->pause ? "pause" : "normal", &l);
	PSTR(w, "*** DISPLAY ***", v->namemode ? "opname" : "opcode", &l);
	print_middle_value(w, "*** SPEED ***", v->speed, &l);
	print_middle_value(w, "*** TOTAL PROCESS ***", vm->number_champions, &l);
	print_middle_value(w, "*** ACTUAL TURN ***", vm->actual_turn, &l);
	if (vm->nbr_turn >= 0)
		print_middle_value(w, "*** END TURN ***", vm->nbr_turn, &l);
	else
		print_middle_str(w, "*** END TURN ***", "none", &l);
	print_middle_value(w, "*** NEXT CHECK ***", CTD - NDV, &l);
	PMV(w, "*** CYCLE TO DIE ***", vm->cycle_to_die, &l);
	PMV(w, "*** CYCLE DELTA ***", CYCLE_DELTA, &l);
	PMV(w, "*** NUMBER LIVE BEFORE DECREASE ***", NBR_LIVE - NLIVE, &l);
	PMV(w, "*** NUMBER CHECK BEFORE DECREASE***", MAX_CHECKS - NCHECK, &l);
	PMV(w, "*** NUMBER PROCESS PLAYER 1 ***", P[0].pc_number, &l);
	PMV(w, "*** NUMBER PROCESS PLAYER 2 ***", P[1].pc_number, &l);
	PMV(w, "*** NUMBER PROCESS PLAYER 3 ***", P[2].pc_number, &l);
	PMV(w, "*** NUMBER PROCESS PLAYER 4 ***", P[3].pc_number, &l);
	PSTR(w, "*** LAST CHAMPION IN LIVE ***", P[vm->last_in_live].name, &l);
	refresh_window(w);
}

void	draw_champion(t_viewer *v, WINDOW *w, t_champion *c)
{
	int				line;
	int				color;

	line = 2;
	if (!c || c->p->dead)
		return (refresh_window(w));
	color = find_color_of(c, v);
	wattron(w, COLOR_PAIR(color));
	print_middle_str(w, c->p->name, c->p->comment, &line);
	print_middle_value(w, "CARY", c->carry, &line);
	line--;
	print_middle_str(w, "LIVE", c->in_live ? "yes" : "no", &line);
	line--;
	PMV(w, "PROCESS DISPLAYED", v->actual_process[c->order], &line);
	line--;
	print_middle_value(w, "POSITION", c->last_position, &line);
	draw_register(w, c, line);
	wattroff(w, COLOR_PAIR(color));
	refresh_window(w);
}

void	draw_header(WINDOW *w)
{
	int l;

	l = 4;
	wattron(w, A_BOLD | COLOR_PAIR(1));
	print_header(w, H1A, H1B, &l);
	print_header(w, H2A, H2B, &l);
	print_header(w, H3A, H3B, &l);
	print_header(w, H4A, H4B, &l);
	print_header(w, H5A, H5B, &l);
	print_header(w, H6A, H6B, &l);
	print_header(w, H7A, H7B, &l);
	print_header(w, H8A, H8B, &l);
	print_header(w, H9A, H9B, &l);
	print_header(w, H10A, H10B, &l);
	wrefresh(w);
	wattroff(w, A_BOLD);
}

void	draw_all(t_vm *vm, t_viewer *v)
{
	int			i;
	t_champion	*ch;

	werase(v->memory);
	werase(v->header);
	werase(v->info);
	i = 0;
	while (i < MAX_PLAYERS)
	{
		werase(v->champion[i]);
		if (!vm->player[i].dead && vm->player[i].pc_number > 0)
		{
			ch = FCO(vm->list_champions, P[i].id, 0, v->actual_process[i]);
			if (ch != NULL)
				draw_champion(v, v->champion[i], ch);
		}
		wrefresh(v->champion[i]);
		i++;
	}
	draw_header(v->header);
	draw_memory(vm, v, v->memory);
	draw_info(vm, v, v->info);
	refresh();
}
