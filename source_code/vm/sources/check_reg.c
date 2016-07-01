/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_reg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleblanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 15:00:23 by aleblanc          #+#    #+#             */
/*   Updated: 2016/06/02 18:22:12 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		check_reg(char *reg)
{
	char	tab[4];

	tab[0] = reg[0];
	tab[1] = 0;
	tab[2] = 0;
	tab[3] = 0;
	if (*(int *)tab > 0 && *(int *)tab < REG_NUMBER + 1)
		return (1);
	return (0);
}

void	cpy_reg(t_champion *ch, int reg, int src)
{
	ch->registre[reg][0] = ch->registre[src][0];
	ch->registre[reg][1] = ch->registre[src][1];
	ch->registre[reg][2] = ch->registre[src][2];
	ch->registre[reg][3] = ch->registre[src][3];
}
