/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 17:39:25 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/05 15:17:39 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	find_arg_type(char code, char type[4], int opcode, t_champion *ch)
{
	unsigned char tmp;

	if (opcode == 1 || opcode == 9 || opcode == 12 || opcode == 15)
	{
		type[0] = 2;
		return ;
	}
	tmp = code;
	type[0] = tmp >> 6;
	tmp = code << 2;
	type[1] = tmp >> 6;
	tmp = code << 4;
	type[2] = tmp >> 6;
	tmp = code << 6;
	type[3] = tmp >> 6;
	move_pc(ch, 1);
}

char	*str_arg(t_vm *vm, int size, int index)
{
	char	*arg;
	int		i;

	arg = ft_strnew(size + 1);
	i = 0;
	while (i < size)
	{
		arg[i] = vm->memory[index_memory(index)];
		index++;
		i++;
	}
	return (arg);
}

void	free_arg(char *arg[4])
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (arg[i])
			ft_strdel(&arg[i]);
		i++;
	}
}

void	find_arg(t_champion *ch, t_vm *vm, char type[4], char *arg[4])
{
	int i;

	i = 0;
	while (i < vm->argc[ch->last_opcode - 1])
	{
		if (type[i] == REG_CODE)
		{
			arg[i] = str_arg(vm, 1, ch->pc);
			move_pc(ch, 1);
		}
		else if (type[i] == DIR_CODE)
		{
			arg[i] = str_arg(vm, vm->direct_size[ch->last_opcode - 1], ch->pc);
			move_pc(ch, vm->direct_size[ch->last_opcode - 1]);
		}
		else if (type[i] == IND_CODE)
		{
			arg[i] = str_arg(vm, 2, ch->pc);
			move_pc(ch, 2);
		}
		i++;
	}
}

void	execute_instruction(t_champion *ch, t_vm *vm)
{
	char	type[4];
	char	*arg[4];

	ft_bzero(type, 4);
	ft_bzero(arg, 4 * sizeof(char*));
	if (ch->op_in_progress == 0)
		ch->op_in_progress = vm->memory[ch->pc];
	change_position(ch, ch->pc);
	if (OIP > 0 && OIP <= 16 && ch->in_progress < vm->duration[OIP - 1] - 1)
	{
		ch->in_progress += 1;
		return ;
	}
	ch->in_progress = 0;
	move_pc(ch, 1);
	ch->last_opcode = ch->op_in_progress;
	if (ch->op_in_progress > 0 && ch->op_in_progress < 17)
	{
		find_arg_type(vm->memory[ch->pc], type, ch->op_in_progress, ch);
		find_arg(ch, vm, type, arg);
		vm->tab_function[ch->op_in_progress - 1](ch, vm, arg, type);
		free_arg(arg);
	}
	ch->op_in_progress = 0;
}
