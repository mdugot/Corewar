/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_sub.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleblanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 15:42:40 by aleblanc          #+#    #+#             */
/*   Updated: 2016/06/05 11:00:49 by aleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	f_sub(t_champion *champion, t_vm *vm, char **arg, char *type)
{
	int		dif;
	int		arg2;

	(void)vm;
	if (type[0] == REG_CODE && type[1] == REG_CODE && type[2] == REG_CODE &&
		check_reg(arg[0]) && check_reg(arg[1]) && check_reg(arg[2]))
	{
		dif = cast_int(champion->registre[cast_int_frone(arg[0][0]) - 1])
			- cast_int(champion->registre[cast_int_frone(arg[1][0]) - 1]);
		arg2 = cast_int_frone(arg[2][0]);
		champion->registre[arg2 - 1][0] = (char)(dif >> 0);
		champion->registre[arg2 - 1][1] = (char)(dif >> 8);
		champion->registre[arg2 - 1][2] = (char)(dif >> 16);
		champion->registre[arg2 - 1][3] = (char)(dif >> 24);
		if (dif == 0)
			champion->carry = 1;
		else
			champion->carry = 0;
	}
}
