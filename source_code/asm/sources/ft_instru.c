/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_instru.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 11:05:08 by cdrouet           #+#    #+#             */
/*   Updated: 2016/05/26 09:30:52 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

char	*instru(char opc)
{
	static char	ins[16][7] = {"live", "ld", "st", "add", "sub", "and", "or",
		"xor", "zjmp", "ldi", "sti", "fork", "lld", "lldi", "lfork", "aff"};

	if (opc <= 0 || opc >= 17)
		error_exit("Bad instruction code", EINVAL);
	return (ins[opc - 1]);
}

int		*arg_val(char opc)
{
	static int	ins[16][3] = {
		{4, 0, 0},
		{6, 1, 0},
		{1, 3, 0},
		{1, 1, 1},
		{1, 1, 1},
		{7, 7, 1},
		{7, 7, 1},
		{7, 7, 1},
		{4, 0, 0},
		{7, 5, 1},
		{1, 7, 5},
		{4, 0, 0},
		{6, 1, 0},
		{7, 5, 1},
		{4, 0, 0},
		{1, 0, 0}
	};

	if (opc <= 0 || opc >= 17)
		error_exit("Bad instruction code", EINVAL);
	return (ins[opc - 1]);
}

int		octet_codage(char opc)
{
	static int	ins[16] = {0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1};

	if (opc <= 0 || opc >= 17)
		error_exit("Bad instruction code", EINVAL);
	return (ins[opc - 1]);
}

int		dir_size(char opc)
{
	static int	ins[16] = {4, 4, 0, 0, 0, 4, 4, 4, 2, 2, 2, 2, 4, 2, 2, 0};

	if (opc <= 0 || opc >= 17)
		error_exit("Bad instruction code", EINVAL);
	return (ins[opc - 1]);
}

int		nb_param(char opc)
{
	static int	ins[16] = {1, 2, 2, 3, 3, 3, 3, 3, 1, 3, 3, 1, 2, 3, 1, 1};

	if (opc <= 0 || opc >= 17)
		error_exit("Bad instruction code", EINVAL);
	return (ins[opc - 1]);
}
