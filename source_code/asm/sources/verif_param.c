/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 11:48:24 by cdrouet           #+#    #+#             */
/*   Updated: 2016/05/31 08:27:37 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

int		is_lab(char *str)
{
	int		i;
	char	*ptr;

	ptr = LABEL_CHARS;
	if (str[0] != LABEL_CHAR)
		return (0);
	i = 0;
	while (str[++i])
		if (!ft_strchr(ptr, str[i]))
			return (0);
	return (1);
}

int		is_some(char opc, int i, t_instruct *a, t_instruct *ins)
{
	int	*p;

	p = arg_val(opc);
	if ((p[i] & 4) && is_dir(a, a->param[i], ins))
		return (1);
	if ((p[i] & 2) && is_ind(a->param[i], ins))
		return (2);
	if ((p[i] & 1) && is_reg(a->param[i]))
		return (3);
	return (0);
}

int		is_dir(t_instruct *ok, char *str, t_instruct *ins)
{
	t_instruct	*tmp;

	if (str[0] != DIRECT_CHAR)
		return (0);
	if (str[1] != LABEL_CHAR)
	{
		if (!ft_strlen(&str[1]) || !ft_strisdigit(&str[1]))
			error_exit(ft_strjoin(ft_itoa(ok->line),
				ft_strjoin("<-line Invalid direct value for ", ok->name)),
				EINVAL);
		else
			return (1);
	}
	tmp = ins;
	while (tmp)
	{
		if (tmp->label && !ft_strcmp(tmp->label, &str[2]))
			return (1);
		tmp = tmp->next;
	}
	error_exit(ft_strjoin(ft_itoa(ok->line),
		ft_strjoin("<-line Unknown label ", &str[2])), EINVAL);
	return (0);
}

int		is_reg(char *str)
{
	return ((str[0] != 'r'
		|| !ft_strlen(&str[1])
		|| !ft_strisdigit(&str[1])
		|| ft_atoi(&str[1]) < 1
		|| ft_atoi(&str[1]) > REG_NUMBER) ? 0 : 1);
}

int		is_ind(char *str, t_instruct *ins)
{
	t_instruct	*tmp;

	if (str[0] != LABEL_CHAR)
	{
		if (!ft_strisdigit(str))
			return (0);
		else
			return (1);
	}
	tmp = ins;
	while (tmp)
	{
		if (tmp->label && !ft_strcmp(tmp->label, &str[1]))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
