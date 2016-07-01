/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_zjmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleblanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 15:36:41 by aleblanc          #+#    #+#             */
/*   Updated: 2016/06/05 11:02:40 by aleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	f_zjmp(t_champion *ch, t_vm *vm, char **arg, char *type)
{
	int		de;

	(void)vm;
	if (type[0] == DIR_CODE && ch->carry == 1)
	{
		de = (int)cast_sh_int(arg[0]) % IDX_MOD;
		ch->pc = index_memory(ch->last_position + de);
	}
}
