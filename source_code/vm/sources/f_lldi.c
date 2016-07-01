/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_lldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleblanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 11:37:58 by aleblanc          #+#    #+#             */
/*   Updated: 2016/06/05 10:56:17 by aleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	f_lldi(t_champion *ch, t_vm *vm, char **arg, char *type)
{
	int		val1;
	int		val2;
	int		de;
	int		i;

	if (type[2] == REG_CODE && check_reg(arg[2]) && ((type[0] == REG_CODE &&
		check_reg(arg[0])) || type[0] == DIR_CODE || type[0] == IND_CODE) &&
		((type[1] == REG_CODE && check_reg(arg[1])) || type[1] == DIR_CODE))
	{
		val1 = convert_sh(ch, vm, arg[0], type[0]);
		val2 = convert_sh(ch, vm, arg[1], type[1]);
		de = (val1 + val2);
		de = ch->last_position + de;
		i = cast_int_frone(arg[2][0]) - 1;
		ch->registre[i][0] = (char)vm->memory[index_memory(de + 3)];
		ch->registre[i][1] = (char)vm->memory[index_memory(de + 2)];
		ch->registre[i][2] = (char)vm->memory[index_memory(de + 1)];
		ch->registre[i][3] = (char)vm->memory[index_memory(de)];
		if (*((int *)ch->registre[i]) == 0)
			ch->carry = 1;
		else
			ch->carry = 0;
	}
}
