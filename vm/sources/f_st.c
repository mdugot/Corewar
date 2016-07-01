/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_st.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleblanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 11:34:27 by aleblanc          #+#    #+#             */
/*   Updated: 2016/06/05 10:58:37 by aleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	f_st(t_champion *ch, t_vm *vm, char **arg, char *type)
{
	int		de;
	int		reg;
	int		pos;

	if (type[0] == REG_CODE && check_reg(arg[0]) && type[1] == IND_CODE)
	{
		de = cast_sh_int(arg[1]) % IDX_MOD;
		reg = cast_int_frone(arg[0][0]) - 1;
		pos = ch->last_position + de;
		vm->memory[index_memory(pos + 3)] = ch->registre[reg][0];
		vm->memory[index_memory(pos + 2)] = ch->registre[reg][1];
		vm->memory[index_memory(pos + 1)] = ch->registre[reg][2];
		vm->memory[index_memory(pos)] = ch->registre[reg][3];
	}
	else if (type[0] == 1 && check_reg(arg[0]) && type[1] == 1
			&& check_reg(arg[0]))
		cpy_reg(ch, cast_int_frone(arg[1][0]) - 1,
				cast_int_frone(arg[0][0]) - 1);
}
