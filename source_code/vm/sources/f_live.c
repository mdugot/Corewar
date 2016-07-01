/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_live.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleblanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 15:58:29 by aleblanc          #+#    #+#             */
/*   Updated: 2016/06/05 17:32:28 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_live(t_player *player)
{
	ft_printf("un processus dit que le joueur %d(%s) est en vie\n",
			player->id, player->name);
}

void	f_live(t_champion *ch, t_vm *vm, char **arg, char *type)
{
	int			id;
	int			i;

	ch->in_live = 1;
	if (type[0] == DIR_CODE)
	{
		id = cast_int_rev(arg[0]);
		vm->nbr_live++;
		i = 0;
		while (i < MAX_PLAYERS)
		{
			if (vm->player[i].id == id && vm->player[i].dead == 0)
			{
				vm->last_in_live = i;
				if (!vm->visual && vm->show_live == 1)
					print_live(&(vm->player[i]));
			}
			i++;
		}
	}
}
