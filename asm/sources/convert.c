/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 10:09:00 by cdrouet           #+#    #+#             */
/*   Updated: 2016/05/25 10:35:28 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

int		search_i_lab(t_instruct *ins, char *lab)
{
	int			ret;
	t_instruct	*tmp;

	tmp = ins;
	ret = 0;
	while (tmp)
	{
		if (tmp->label && !ft_strcmp(tmp->label, lab))
			return (ret);
		else
			ret += tmp->index;
		tmp = tmp->next;
	}
	ret = 0;
	tmp = ins->previous;
	while (tmp)
	{
		ret -= tmp->index;
		if (tmp->label && !ft_strcmp(tmp->label, lab))
			return (ret);
		tmp = tmp->previous;
	}
	return (ret);
}

int		tab_instru(char *str)
{
	static const char	in[16][6] = {"live", "ld", "st", "add", "sub", "and",
		"or", "xor", "zjmp", "ldi", "sti", "fork", "lld", "lldi", "lfork",
		"aff"};
	int					i;

	i = -1;
	while (++i < 16)
		if (!ft_strcmp(in[i], str))
			return (i);
	return (0);
}

int		convert(t_instruct *ins)
{
	t_instruct	*tmp;
	int			len;

	tmp = ins;
	len = 0;
	while (tmp)
	{
		if (tmp->name)
			convert_all(tmp, ins);
		else
			tmp->index = 0;
		len += tmp->index;
		tmp = tmp->next;
	}
	tmp = ins;
	while (tmp)
	{
		if (tmp->name)
			convert_param(tmp, ins);
		tmp = tmp->next;
	}
	return (len);
}
