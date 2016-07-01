/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_add.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleblanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 14:58:44 by aleblanc          #+#    #+#             */
/*   Updated: 2016/06/05 10:49:21 by aleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	f_add(t_champion *champion, t_vm *vm, char **arg, char *type)
{
	int		sum;
	int		arg2;

	(void)vm;
	if (type[0] == REG_CODE && type[1] == REG_CODE && type[2] == REG_CODE &&
			check_reg(arg[0]) && check_reg(arg[1]) && check_reg(arg[2]))
	{
		sum = cast_int(champion->registre[cast_int_frone(arg[0][0]) - 1])
			+ cast_int(champion->registre[cast_int_frone(arg[1][0]) - 1]);
		arg2 = cast_int_frone(arg[2][0]) - 1;
		champion->registre[arg2][0] = (char)(sum >> 0);
		champion->registre[arg2][1] = (char)(sum >> 8);
		champion->registre[arg2][2] = (char)(sum >> 16);
		champion->registre[arg2][3] = (char)(sum >> 24);
		if (sum == 0)
			champion->carry = 1;
		else
			champion->carry = 0;
	}
}
