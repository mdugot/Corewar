/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_fork.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 15:00:57 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/05 10:48:20 by aleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	f_fork(t_champion *champion, t_vm *vm, char **arg, char *type)
{
	short int	index;
	t_champion	*new;

	(void)type;
	index = cast_sh_int(arg[0]);
	index = index % IDX_MOD;
	new = ft_memalloc(sizeof(t_champion));
	ft_memcpy(new, champion, sizeof(t_champion));
	new->pc = index_memory(index + new->last_position);
	new->in_progress = 0;
	new->op_in_progress = 0;
	new->born_in = vm->actual_turn;
	change_position(new, new->pc);
	add_process(vm, new);
	vm->number_champions += 1;
	vm->player[champion->order].pc_number += 1;
}

void	f_lfork(t_champion *champion, t_vm *vm, char **arg, char *type)
{
	short int	index;
	t_champion	*new;

	(void)type;
	index = cast_sh_int(arg[0]);
	new = ft_memalloc(sizeof(t_champion));
	ft_memcpy(new, champion, sizeof(t_champion));
	new->pc = index_memory(index + new->last_position);
	new->in_progress = 0;
	new->op_in_progress = 0;
	new->born_in = vm->actual_turn;
	change_position(new, new->pc);
	add_process(vm, new);
	vm->number_champions += 1;
	vm->player[champion->order].pc_number += 1;
}
