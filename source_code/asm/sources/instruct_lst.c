/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruct_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 11:56:37 by cdrouet           #+#    #+#             */
/*   Updated: 2016/05/30 15:12:01 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

int					ft_pstrlen(char **pstr)
{
	int		i;

	i = 0;
	while (pstr[i])
		i++;
	return (i);
}

int					verif_label(char *label)
{
	char	*ptr;
	int		i;
	int		len;

	ptr = LABEL_CHARS;
	if (ft_strlen(label) == 1 || label[ft_strlen(label) - 1] != LABEL_CHAR)
		return (0);
	i = -1;
	len = ft_strlen(label) - 1;
	while (++i < len)
		if (!ft_strchr(ptr, label[i]))
			return (0);
	return (1);
}

void				replace_c(char *str, char c, char r)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			str[i] = r;
}

static t_instruct	*init_ins(int li)
{
	t_instruct	*ins;

	ins = (t_instruct*)malloc(sizeof(t_instruct));
	ins->next = NULL;
	ins->previous = NULL;
	ins->name = NULL;
	ins->param = NULL;
	ins->line = li;
	return (ins);
}

t_instruct			*new_instruct(int li, t_instruct **lst, char *all, int fd)
{
	t_instruct	*ins;
	int			ret;
	int			ret_gnl;

	ins = init_ins(li);
	ret = check_label(&(ins->label), all);
	if (ret == 1)
	{
		while ((ret_gnl = get_next_line(fd, &all)) > 0)
			if (lin(1) && !void_str(all))
				break ;
		ret--;
		if (check_label(NULL, all))
		{
			add_end_lst(lst, ins);
			add_end_lst(lst, new_instruct(lin(0), lst, all, fd));
			return (NULL);
		}
		else if (ret_gnl <= 0)
			return (ins);
	}
	check_instruction(&(ins->param), &(ins->name), all, ret);
	return (ins);
}
