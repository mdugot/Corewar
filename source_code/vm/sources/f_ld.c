/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_ld.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleblanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 14:50:07 by aleblanc          #+#    #+#             */
/*   Updated: 2016/06/05 10:51:44 by aleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	f_ld(t_champion *ch, t_vm *vm, char **arg, char *type)
{
	int		arg1;
	int		val;

	if ((type[0] == IND_CODE || type[0] == DIR_CODE) && type[1] == REG_CODE &&
		check_reg(arg[1]))
	{
		val = convert(ch, vm, arg[0], type[0]);
		arg1 = cast_int_frone(arg[1][0]) - 1;
		ch->registre[arg1][0] = (char)(val >> 0);
		ch->registre[arg1][1] = (char)(val >> 8);
		ch->registre[arg1][2] = (char)(val >> 16);
		ch->registre[arg1][3] = (char)(val >> 24);
		if (val == 0)
			ch->carry = 1;
		else
			ch->carry = 0;
	}
}
