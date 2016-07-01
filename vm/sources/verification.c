/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verification.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 14:31:51 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/05 17:15:56 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	verify_champion(t_champion *ch, t_vm *vm, t_list *elem)
{
	if (ch->in_live > 0)
		ch->in_live = 0;
	else
	{
		vm->player[ch->order].pc_number -= 1;
		vm->number_champions -= 1;
		change_position(ch, -1);
		if (vm->viewer)
		{
			vm->viewer->actual_process[ch->order] -= 1;
			if (vm->viewer->actual_process[ch->order] < 0)
				vm->viewer->actual_process[ch->order] = 0;
		}
		ft_lstdelin_memdel(&vm->list_champions, elem);
	}
}

void	decrease_cycle(t_vm *vm)
{
	static int	last_decrease = -1;

	if (last_decrease >= vm->actual_turn)
		return ;
	last_decrease = vm->actual_turn;
	vm->cycle_to_die -= CYCLE_DELTA;
	if (vm->cycle_to_die < 0)
		vm->cycle_to_die = 0;
}

void	verify_live(t_vm *vm)
{
	t_list	*tmp;
	t_list	*next;

	if (vm->nbr_live > NBR_LIVE)
	{
		vm->nbr_live = 0;
		decrease_cycle(vm);
	}
	if (vm->nbr_check > MAX_CHECKS)
	{
		vm->nbr_check = 0;
		decrease_cycle(vm);
	}
	vm->nbr_live = 0;
	vm->nbr_check += 1;
	vm->next_die_verification = 0;
	tmp = vm->list_champions;
	while (tmp && vm->number_champions > 0)
	{
		next = tmp->next;
		verify_champion(tmp->content, vm, tmp);
		tmp = next;
	}
}
