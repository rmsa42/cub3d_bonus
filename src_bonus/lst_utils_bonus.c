/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 10:05:29 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/08 15:32:45 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_lst	*lst_last(t_lst *lst)
{
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	lst_add_back(t_lst **lst, t_lst *new)
{
	t_lst	*temp;

	if (*lst)
	{
		temp = lst_last(*lst);
		temp->next = new;
	}
	else
		*lst = new;
}

t_lst	*create_node(void *data)
{
	t_lst	*node;

	node = ft_calloc(1, sizeof(t_lst));
	node->data = data;
	node->next = NULL;
	return (node);
}

/* void	elim_ent(t_base_lst *objs, t_base_lst *node)
{
	t_base_lst	*last;
	
	while (objs != NULL && objs != node)
	{
		last = objs;
		objs = objs->next;
	}
	last->next = node->next;
	free(node->data);
	free(node);
	node = NULL;
} */

int	lst_size(t_lst *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	print_lst(t_lst *lst)
{
	while (lst != NULL)
	{
		printf("%d\n", ((t_game_obj *)lst->data)->type);
		lst = lst->next;
	}
}
