/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleblanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 11:55:11 by aleblanc          #+#    #+#             */
/*   Updated: 2016/06/02 18:21:40 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			cast_int(char *tab)
{
	char integer[4];

	integer[0] = tab[0];
	integer[1] = tab[1];
	integer[2] = tab[2];
	integer[3] = tab[3];
	return (*((int *)integer));
}

int			cast_int_rev(char *tab)
{
	char integer[4];

	integer[0] = tab[3];
	integer[1] = tab[2];
	integer[2] = tab[1];
	integer[3] = tab[0];
	return (*((int *)integer));
}

short int	cast_sh_int(char *tab)
{
	char integer[2];

	integer[0] = tab[1];
	integer[1] = tab[0];
	return (*((short int *)integer));
}

int			cast_int_frone(char tab)
{
	char integer[4];

	integer[0] = tab;
	integer[1] = 0;
	integer[2] = 0;
	integer[3] = 0;
	return (*((int *)integer));
}

int			index_memory(int index)
{
	if (index >= 0)
		return (index % MEM_SIZE);
	else
		return (MEM_SIZE - (ABS(index) % MEM_SIZE));
}
