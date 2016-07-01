/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_xor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleblanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 08:56:21 by aleblanc          #+#    #+#             */
/*   Updated: 2016/06/05 11:07:49 by aleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	f_xor(t_champion *ch, t_vm *vm, char **arg, char *type)
{
	int		re;
	int		i;
	int		val1;
	int		val2;

	if (type[2] == REG_CODE && check_reg(arg[2]) && ((type[0] == REG_CODE &&
		check_reg(arg[0])) || type[0] == DIR_CODE || type[0] == IND_CODE) &&
		((type[1] == REG_CODE && check_reg(arg[1])) || type[1] == DIR_CODE ||
		type[1] == IND_CODE))
	{
		val1 = convert(ch, vm, arg[0], type[0]);
		val2 = convert(ch, vm, arg[1], type[1]);
		re = val1 ^ val2;
		i = cast_int_frone(arg[2][0]) - 1;
		ch->registre[i][0] = (char)(re >> 0);
		ch->registre[i][1] = (char)(re >> 8);
		ch->registre[i][2] = (char)(re >> 16);
		ch->registre[i][3] = (char)(re >> 24);
		if (re == 0)
			ch->carry = 1;
		else
			ch->carry = 0;
	}
}
