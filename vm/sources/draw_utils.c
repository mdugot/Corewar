/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 18:00:38 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/04 17:16:48 by aleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		find_champion_color(t_vm *vm, t_viewer *v, int position)
{
	int id;
	int	i;

	if (v->process_position[position])
		id = v->process_position[position]->p->id;
	else
		return (-1);
	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (vm->player[i].id == id)
			return (v->champion_color[i]);
		i++;
	}
	return (-1);
}

int		find_mem_color(t_vm *vm, t_viewer *v, int i, int y)
{
	int color;
	int champion_color;

	(void)champion_color;
	(void)v;
	champion_color = find_champion_color(vm, v, i);
	if (champion_color > 0)
	{
		wattron(v->memory, A_REVERSE);
		return (champion_color);
	}
	color = 4;
	if (i % 2 == y % 2)
		color = 5;
	if (vm->memory[i] == 0)
		color += 2;
	return (color);
}

int		find_color_of(t_champion *c, t_viewer *v)
{
	int		i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (c->vm->player[i].id == c->numero)
			return (v->champion_color[i]);
		i++;
	}
	return (0);
}

void	draw_register(WINDOW *w, t_champion *c, int line)
{
	int				i;
	unsigned int	*tmp;

	i = 0;
	print_middle_simple(w, "REGISTER", A_BOLD | A_UNDERLINE, &line);
	while (i < REG_NUMBER)
	{
		tmp = (unsigned int*)c->registre[i];
		if (*tmp)
			print_middle_hexa(w, *tmp, A_BOLD, &line);
		else
			print_middle_hexa(w, *tmp, A_DIM, &line);
		i++;
	}
}

void	refresh_window(WINDOW *window)
{
	wattron(window, COLOR_PAIR(3));
	wborder(window, '|', '|', '-', '-', '+', '+', '+', '+');
	wattron(window, COLOR_PAIR(1));
	wrefresh(window);
}
