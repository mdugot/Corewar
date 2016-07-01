/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruct_lst_aj.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 14:09:45 by cdrouet           #+#    #+#             */
/*   Updated: 2016/05/31 08:46:46 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

int		verif_nasm(char **argv)
{
	if ((!ft_strcmp(argv[1], "-n")
		|| !ft_strcmp(argv[2], "-n"))
			&& (!ft_strcmp(&argv[1][ft_strlen(argv[1]) - 4], ".cor")
		|| !ft_strcmp(&argv[2][ft_strlen(argv[2]) - 4], ".cor")))
		return (1);
	return (0);
}

void	add_end_lst(t_instruct **lst, t_instruct *new)
{
	t_instruct	*tmp;

	if (new == NULL)
		return ;
	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	tmp->next->previous = tmp;
}
