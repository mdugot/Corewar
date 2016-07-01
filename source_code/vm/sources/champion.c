/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 17:49:31 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/05 15:17:35 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		change_position(t_champion *ch, int new)
{
	int			old;
	t_viewer	*v;

	old = ch->last_position;
	ch->last_position = new;
	if (ch->vm->viewer)
	{
		v = ch->vm->viewer;
		if (v->process_position[old] == ch)
			v->process_position[old] = NULL;
		if (new >= 0)
			v->process_position[new] = ch;
	}
}

int			cmp_champion(void *a1, void *a2)
{
	t_champion *c1;
	t_champion *c2;

	c1 = (t_champion*)a1;
	c2 = (t_champion*)a2;
	return (c2->n - c1->n);
}

int			available_number(t_list *list, t_list *elem, int n)
{
	t_champion *ch;

	if (elem == NULL)
		return (n);
	ch = (t_champion*)elem->content;
	if (ch->numero == n)
		return (available_number(list, list, n + 1));
	else
		return (available_number(list, elem->next, n));
}

void		add_process(t_vm *vm, t_champion *ch)
{
	static int	n = 0;
	t_list		*new;

	ch->n = n;
	n++;
	new = ft_lstnew_noalloc(ch, sizeof(t_champion));
	ft_lstadd_sorted(&vm->list_champions, new, cmp_champion);
}
