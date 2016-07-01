/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleblanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 15:39:23 by aleblanc          #+#    #+#             */
/*   Updated: 2016/06/02 18:23:52 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		convert_nomod(t_champion *ch, t_vm *vm, char *arg, char type)
{
	int		val;
	int		de;
	int		pos;
	char	tab[4];

	val = 0;
	if (type == 1)
		val = cast_int(ch->registre[cast_int_frone(arg[0]) - 1]);
	else if (type == 2)
		val = cast_int_rev(arg);
	else if (type == 3)
	{
		de = cast_sh_int(arg);
		pos = ch->last_position + de;
		ft_bzero(tab, 4);
		tab[0] = (char)vm->memory[index_memory(pos + 3)];
		tab[1] = (char)vm->memory[index_memory(pos + 2)];
		tab[2] = (char)vm->memory[index_memory(pos + 1)];
		tab[3] = (char)vm->memory[index_memory(pos)];
		val = *((int *)tab);
	}
	return (val);
}

int		convert(t_champion *ch, t_vm *vm, char *arg, char type)
{
	int		val;
	int		de;
	int		pos;
	char	tab[4];

	val = 0;
	if (type == 1)
		val = cast_int(ch->registre[cast_int_frone(arg[0]) - 1]);
	else if (type == 2)
		val = cast_int_rev(arg);
	else if (type == 3)
	{
		de = cast_sh_int(arg) % IDX_MOD;
		pos = ch->last_position + de;
		ft_bzero(tab, 4);
		tab[0] = (char)vm->memory[index_memory(pos + 3)];
		tab[1] = (char)vm->memory[index_memory(pos + 2)];
		tab[2] = (char)vm->memory[index_memory(pos + 1)];
		tab[3] = (char)vm->memory[index_memory(pos)];
		val = *((int *)tab);
	}
	return (val);
}

int		convert_sh(t_champion *ch, t_vm *vm, char *arg, char type)
{
	int		val;
	int		de;
	int		pos;
	char	tab[4];

	val = 0;
	if (type == 1)
		val = cast_int(ch->registre[cast_int_frone(arg[0]) - 1]);
	else if (type == 2)
		val = (int)cast_sh_int(arg);
	else if (type == 3)
	{
		de = cast_sh_int(arg) % IDX_MOD;
		pos = ch->last_position + de;
		ft_bzero(tab, 4);
		tab[0] = (char)vm->memory[index_memory(pos + 3)];
		tab[1] = (char)vm->memory[index_memory(pos + 2)];
		tab[2] = (char)vm->memory[index_memory(pos + 1)];
		tab[3] = (char)vm->memory[index_memory(pos)];
		val = *((int *)tab);
	}
	return (val);
}
