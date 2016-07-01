/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 17:10:34 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/06 12:20:02 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	usage_error(void)
{
	ft_putendl_fd("corewar : wrong usage", 2);
	ft_putendl_fd(
"usage : corewar [-s] [-v] [-dump nbr_cycles] [[-n number] champion1.cor] ..."
, 2);
	exit(1);
}

void	add_champion(t_vm *vm, char *name, int n)
{
	t_champion	*ch;
	static int	order = 0;

	if (vm->number_champions >= MAX_PLAYERS)
	{
		ft_putendl_fd("Too many champions", 2);
		exit(1);
	}
	n = available_number(vm->list_champions, vm->list_champions, n);
	ch = read_champion(name, n, vm, order);
	ch->order = order;
	ch->born_in = -1;
	ch->p = &(vm->player[order]);
	vm->player[order].pc_number = 1;
	vm->player[order].first_process = ch;
	order++;
	add_process(vm, ch);
	vm->number_champions += 1;
}

void	read_arg(int argc, char **argv, t_vm *vm)
{
	int		i;
	int		tmp;

	i = 0;
	while (++i < argc)
		if (!ft_strcmp("-dump", argv[i]))
		{
			if (i >= argc - 1 || !ft_isint(argv[i + 1], &tmp) || tmp < 0)
				usage_error();
			vm->nbr_turn = tmp;
			i++;
		}
		else if (!ft_strcmp("-n", argv[i]))
		{
			if (i >= argc - 2 || !ft_isint(argv[i + 1], &tmp))
				usage_error();
			add_champion(vm, argv[i + 2], tmp);
			i += 2;
		}
		else if (!ft_strcmp("-v", argv[i]))
			vm->visual = 1;
		else if (!ft_strcmp("-s", argv[i]))
			vm->show_live = 0;
		else
			add_champion(vm, argv[i], 1);
}

int		main(int argc, char **argv)
{
	t_vm	*vm;
	int		on;

	if (argc <= 1)
		usage_error();
	vm = init_vm();
	read_arg(argc, argv, vm);
	if (vm->number_champions <= 0)
		usage_error();
	dispatch_champions(vm);
	on = 1;
	if (vm->visual)
		init_visual(vm);
	while ((on = one_turn(vm)) || vm->visual)
	{
		if (vm->visual && (vm->actual_turn % vm->viewer->speed == 0 || !on))
			if (update_visual(vm))
				break ;
	}
	if (vm->visual)
		endwin();
	return (0);
}
