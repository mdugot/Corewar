/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 16:01:56 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/05 16:03:52 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	send_in_vm(t_vm *vm, t_player *p, int pc)
{
	int			size;
	char		*memory;
	t_champion	*champion;

	champion = find_champion_id(vm->list_champions, p->id);
	size = p->size;
	memory = p->memory;
	champion->pc = pc;
	change_position(champion, pc);
	ft_memcpy(&vm->memory[pc], memory, size);
}

void	sort_player(t_vm *vm, t_player p[MAX_PLAYERS])
{
	int			i;
	t_player	tmp;

	i = 0;
	while (i < vm->number_champions)
	{
		if (i > 0 && p[i].id > p[i - 1].id)
		{
			ft_memcpy(&tmp, &p[i], sizeof(t_player));
			ft_memcpy(&p[i], &p[i - 1], sizeof(t_player));
			ft_memcpy(&p[i - 1], &tmp, sizeof(t_player));
			i--;
		}
		else
			i++;
	}
	i = 0;
	while (i < vm->number_champions)
	{
		vm->player[i].first_process->order = i;
		vm->player[i].first_process->p = &(vm->player[i]);
		i++;
	}
}

void	dispatch_champions(t_vm *vm)
{
	int		gap;
	int		i;

	gap = MEM_SIZE / vm->number_champions;
	i = 0;
	sort_player(vm, vm->player);
	while (i < vm->number_champions)
	{
		send_in_vm(vm, &vm->player[i], gap * i);
		i++;
	}
}
