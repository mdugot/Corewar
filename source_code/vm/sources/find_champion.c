/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_champion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 17:51:10 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/04 20:10:19 by aleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			champion_here(t_list *elem, int position)
{
	t_champion	*ch;

	if (elem == NULL)
		return (-1);
	ch = (t_champion*)elem->content;
	if (ch->last_position == position)
		return (ch->numero);
	else
		return (champion_here(elem->next, position));
}

t_champion	*find_champion(t_list *elem, int actual, int n)
{
	if (elem == NULL)
		return (NULL);
	if (actual == n)
		return (elem->content);
	else
		return (find_champion(elem->next, actual + 1, n));
}

t_champion	*find_champion_id(t_list *elem, int id)
{
	t_champion *ch;

	if (elem == NULL)
		return (NULL);
	ch = (t_champion*)elem->content;
	if (ch->numero == id)
		return (elem->content);
	else
		return (find_champion_id(elem->next, id));
}

t_champion	*find_champion_order(t_list *elem, int id, int actual, int n)
{
	t_champion *ch;

	if (elem == NULL)
		return (NULL);
	ch = (t_champion*)elem->content;
	if (ch->numero == id)
	{
		if (actual == n)
			return (elem->content);
		actual++;
		return (find_champion_order(elem->next, id, actual, n));
	}
	else
		return (find_champion_order(elem->next, id, actual, n));
}
