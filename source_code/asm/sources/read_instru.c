/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_instru.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 10:24:01 by cdrouet           #+#    #+#             */
/*   Updated: 2016/05/30 14:37:22 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void		replace_comment(char *str)
{
	int	i;
	int	ok;

	i = -1;
	ok = 0;
	while (str[++i])
	{
		if (str[i] == COMMENT_CHAR)
			ok = 1;
		if (ok)
			str[i] = '\0';
	}
}

int			check_label(char **lab, char *line)
{
	if (lab)
		(*lab) = NULL;
	line = ft_strtrim(line);
	if (!ft_strchr(line, LABEL_CHAR) || !verif_label(
		ft_strsub(line, 0, (int)(ft_strchr(line, LABEL_CHAR) - line) + 1)))
		return (0);
	if (lab)
		(*lab) = ft_strsub(line, 0, (int)(ft_strchr(line, LABEL_CHAR) - line));
	return (((ft_strlen(line) - 1)
		== (unsigned long)(ft_strchr(line, LABEL_CHAR) - line)
			? 1 : 2));
}

int			check_instruction(char ***param,
				char **instru, char *line, int label)
{
	char	*new;
	char	**split;

	if (label)
		line = ft_strchr(line, LABEL_CHAR) + 1;
	new = ft_strtrim(line);
	replace_c(new, '	', ' ');
	clean_space(new);
	split = ft_strsplit(new, ' ');
	if (ft_pstrlen(split) != 2)
		error_exit(ft_strjoin("Syntax error - Bad label or instruction line:",
			ft_itoa(lin(0))), EINVAL);
	if (!verif_instru(split[0]))
		error_exit(ft_strjoin("Syntax error - Bad instruction name line:",
			ft_itoa(lin(0))), EINVAL);
	(*instru) = ft_strsub(split[0], 0, ft_strlen(split[0]));
	(*param) = ft_strsplit(split[1], SEPARATOR_CHAR);
	return (1);
}

t_instruct	*read_instruct(int fd)
{
	t_instruct	*ins;
	char		*line;
	int			ret;

	ins = NULL;
	line = NULL;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		lin(1);
		replace_comment(line);
		while (ret > 0 && void_str(line))
		{
			ret = get_next_line(fd, &line);
			if (ret > 0)
				lin(1);
			replace_comment(line);
		}
		if (ret > 0)
			add_end_lst(&ins, new_instruct(lin(0), &ins, line, fd));
	}
	return (ins);
}
