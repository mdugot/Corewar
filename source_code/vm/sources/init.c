/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 18:10:48 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/05 17:40:58 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	init_duration(int duration[16])
{
	duration[0] = 10;
	duration[1] = 5;
	duration[2] = 5;
	duration[3] = 10;
	duration[4] = 10;
	duration[5] = 6;
	duration[6] = 6;
	duration[7] = 6;
	duration[8] = 20;
	duration[9] = 25;
	duration[10] = 25;
	duration[11] = 800;
	duration[12] = 10;
	duration[13] = 50;
	duration[14] = 1000;
	duration[15] = 2;
}

void	init_argc(int argc[16])
{
	argc[0] = 1;
	argc[1] = 2;
	argc[2] = 2;
	argc[3] = 3;
	argc[4] = 3;
	argc[5] = 3;
	argc[6] = 3;
	argc[7] = 3;
	argc[8] = 1;
	argc[9] = 3;
	argc[10] = 3;
	argc[11] = 1;
	argc[12] = 2;
	argc[13] = 3;
	argc[14] = 1;
	argc[15] = 1;
}

void	init_direct_size(int direct_size[16])
{
	direct_size[0] = 4;
	direct_size[1] = 4;
	direct_size[2] = 04;
	direct_size[3] = 04;
	direct_size[4] = 04;
	direct_size[5] = 4;
	direct_size[6] = 4;
	direct_size[7] = 4;
	direct_size[8] = 2;
	direct_size[9] = 2;
	direct_size[10] = 2;
	direct_size[11] = 2;
	direct_size[12] = 4;
	direct_size[13] = 2;
	direct_size[14] = 2;
	direct_size[15] = 04;
}

t_vm	*init_vm(void)
{
	t_vm	*vm;
	int		i;

	vm = ft_memalloc(sizeof(t_vm));
	vm->nbr_turn = -1;
	vm->show_live = 1;
	vm->cycle_to_die = CYCLE_TO_DIE;
	init_duration(vm->duration);
	init_argc(vm->argc);
	init_direct_size(vm->direct_size);
	initialise_function(vm);
	i = 0;
	while (i < MAX_PLAYERS)
	{
		vm->player[i].dead = 1;
		i++;
	}
	return (vm);
}
