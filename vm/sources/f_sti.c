/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_sti.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleblanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 14:43:31 by aleblanc          #+#    #+#             */
/*   Updated: 2016/06/05 11:08:11 by aleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	f_sti(t_champion *ch, t_vm *vm, char **arg, char *type)
{
	int		val1;
	int		val2;
	int		de;
	int		i;

	if (type[0] == REG_CODE && check_reg(arg[0]) && ((type[1] == REG_CODE &&
		check_reg(arg[1])) || type[1] == DIR_CODE || type[1] == IND_CODE) &&
		((type[2] == REG_CODE && check_reg(arg[2])) || type[2] == DIR_CODE))
	{
		val1 = convert_sh(ch, vm, arg[1], type[1]);
		val2 = convert_sh(ch, vm, arg[2], type[2]);
		de = (val1 + val2) % IDX_MOD;
		de = ch->last_position + de;
		i = cast_int_frone(arg[0][0]) - 1;
		vm->memory[index_memory(de)] = (char)ch->registre[i][3];
		vm->memory[index_memory(de + 1)] = (char)ch->registre[i][2];
		vm->memory[index_memory(de + 2)] = (char)ch->registre[i][1];
		vm->memory[index_memory(de + 3)] = (char)ch->registre[i][0];
	}
}
