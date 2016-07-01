/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 16:50:20 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/05 15:01:46 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	initialise_function(t_vm *vm)
{
	vm->tab_function[0] = f_live;
	vm->tab_function[1] = f_ld;
	vm->tab_function[2] = f_st;
	vm->tab_function[3] = f_add;
	vm->tab_function[4] = f_sub;
	vm->tab_function[5] = f_and;
	vm->tab_function[6] = f_or;
	vm->tab_function[7] = f_xor;
	vm->tab_function[8] = f_zjmp;
	vm->tab_function[9] = f_ldi;
	vm->tab_function[10] = f_sti;
	vm->tab_function[11] = f_fork;
	vm->tab_function[12] = f_lld;
	vm->tab_function[13] = f_lldi;
	vm->tab_function[14] = f_lfork;
	vm->tab_function[15] = f_aff;
}

void	print_vm(t_vm *vm)
{
	int i;

	if (vm->visual)
		return ;
	i = 0;
	while (i < MEM_SIZE)
	{
		if (i == 0)
			ft_putstr("0x");
		if (i % 64 == 0)
			ft_printf("%#.4x : ", i);
		ft_printf("%.2hhx ", vm->memory[i]);
		if (i % 64 == 63)
			ft_putendl("");
		i++;
	}
}

void	end_game(t_vm *vm)
{
	int			last;
	static int	print_victory = 0;

	last = vm->last_in_live;
	if (!print_victory && !vm->visual)
	{
		print_victory = 1;
		ft_printf("le joueur %d(%s) a gagne\n", P[last].id, P[last].name);
	}
}

int		one_turn(t_vm *vm)
{
	t_list *tmp;

	if (vm->number_champions <= 0)
	{
		end_game(vm);
		return (0);
	}
	if (vm->actual_turn >= vm->nbr_turn && vm->nbr_turn >= 0)
	{
		print_vm(vm);
		return (0);
	}
	vm->next_die_verification += 1;
	vm->actual_turn += 1;
	tmp = vm->list_champions;
	while (tmp)
	{
		execute_instruction((t_champion*)tmp->content, vm);
		tmp = tmp->next;
	}
	if (vm->next_die_verification >= vm->cycle_to_die)
		verify_live(vm);
	return (1);
}
