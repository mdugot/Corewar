/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_aff.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleblanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 09:04:04 by aleblanc          #+#    #+#             */
/*   Updated: 2016/06/05 17:32:24 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	f_aff(t_champion *ch, t_vm *vm, char **arg, char *type)
{
	int		val;

	(void)vm;
	if (type[0] == REG_CODE && check_reg(arg[0]))
	{
		val = cast_int(ch->registre[cast_int_frone(arg[0][0]) - 1]) % IDX_MOD;
		if (vm->visual == 0 && vm->show_live == 1)
			write(1, &val, 4);
	}
}
