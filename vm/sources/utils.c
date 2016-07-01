/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 17:56:32 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/02 17:57:16 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	move_pc(t_champion *ch, int move)
{
	while (move)
	{
		ch->pc += SIGN(move);
		if (ch->pc < 0)
			ch->pc = MEM_SIZE - 1;
		else if (ch->pc >= MEM_SIZE)
			ch->pc = 0;
		move -= SIGN(move);
	}
}
