/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 08:12:49 by cdrouet           #+#    #+#             */
/*   Updated: 2016/05/26 09:23:05 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static void	calc_ocp(t_instruct *ins, int *j, int k)
{
	if (j[k] == 1)
		ins->ocp = (ins->ocp + DIR_CODE) << 2;
	else if (j[k] >= 2)
		ins->ocp =
			(ins->ocp + ((j[k] == 2) ? IND_CODE : REG_CODE)) << 2;
	else
		ins->ocp = ins->ocp << 2;
	if (j[k])
		ins->index += (0b00000001 << ((j[k] == 1)
					? (dir_size(ins->opc) / 2) : 3 - j[k]));
}

void		convert_all(t_instruct *ins, t_instruct *start)
{
	int		i;
	int		j[3];
	int		k;

	i = 0;
	k = -1;
	j[0] = 0;
	j[1] = 0;
	j[2] = 0;
	ins->opc = tab_instru(ins->name) + 1;
	if (ft_pstrlen(ins->param) != nb_param(ins->opc))
		error_exit(ft_strjoin(ft_itoa(ins->line),
			ft_strjoin("<-line Bad number of arg in ", ins->name)), EINVAL);
	while (++k < nb_param(ins->opc))
		if (!(j[k] = is_some(ins->opc, k, ins, start)))
			error_exit(ft_strjoin(ft_itoa(ins->line),
				ft_strjoin("<-line Bad argument in ", ins->name)), EINVAL);
	ins->ocp = 0;
	ins->index = 1 + octet_codage(ins->opc);
	k = -1;
	if (octet_codage(ins->opc))
		while (++k < 3)
			calc_ocp(ins, j, k);
	else
		ins->index += (0b00000001 << (dir_size(ins->opc) / 2));
}

static void	encode(t_instruct *ins, t_instruct *start, int *dec, int i)
{
	int		dir;
	short	ind;

	if (is_dir(ins, ins->param[i], start))
	{
		if (is_lab(&(ins->param[i][1])))
			dir = search_i_lab(ins, &(ins->param[i][2]));
		else
			dir = ft_atoi(&(ins->param[i][1]));
		endian(&dir, sizeof(dir));
		*(int *)(ins->byte_param + (*dec)) = dir;
		(*dec) += 4;
	}
	else if (is_ind(ins->param[i], start))
	{
		if (is_lab(ins->param[i]))
			ind = (short)search_i_lab(ins, &(ins->param[i][1]));
		else
			ind = (short)ft_atoi(ins->param[i]);
		endian(&ind, sizeof(ind));
		*(short *)(ins->byte_param + (*dec)) = ind;
		(*dec) += 2;
	}
}

void		convert_param(t_instruct *ins, t_instruct *start)
{
	int		i;
	int		dec;
	short	dir;

	ins->byte_len = ins->index - (1 + octet_codage(ins->opc));
	ins->byte_param = ft_strnew(ins->byte_len);
	i = -1;
	dec = 0;
	while (ins->param[++i])
		if (dir_size(ins->opc) == 2 && is_dir(ins, ins->param[i], start))
		{
			if (is_lab(&(ins->param[i][1])))
				dir = (short)search_i_lab(ins, &(ins->param[i][2]));
			else
				dir = (short)ft_atoi(&(ins->param[i][1]));
			endian(&dir, sizeof(dir));
			*(short *)(ins->byte_param + dec) = dir;
			dec += 2;
		}
		else if (!is_reg(ins->param[i]))
			encode(ins, start, &dec, i);
		else
			ins->byte_param[dec++] = ft_atoi(&(ins->param[i][1]));
}
