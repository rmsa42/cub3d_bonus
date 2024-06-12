/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:57:01 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/12 16:24:38 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	print_list(t_list *lst)
{
	t_objs	*obj;
	
	while (lst != NULL)
	{
		obj = (t_objs *)lst->content;
		if (obj->type == ENEMY)
			printf("Enemy\n");
		else if (obj->type == BALL)
			printf("Ball\n");
		else
			printf("Sprite\n");
		lst = lst->next;
	}
}

t_sort	*dist_array(t_list *objs_lst, t_v2D pl_pos)
{
	t_sort	*dist_ar;
	t_objs	*obj;
	t_v2D	vector;
	int		i;

	dist_ar = ft_calloc((ft_lstsize(objs_lst)), sizeof(t_sort));
	i = 0;
	while (objs_lst)
	{
		obj = (t_objs *)objs_lst->content;
		vector.x = pl_pos.x - obj->pos.x;
		vector.y = pl_pos.y - obj->pos.y;
		dist_ar[i].order = i;
		dist_ar[i].dist = length_vector(vector);
		objs_lst = objs_lst->next;
		i++;
	}
	return (dist_ar);
}

void	sort_array(t_sort *dist_ar, t_list *head)
{
	t_sort	temp;
	int		i;
	int		j;
	int		len;

	i = 0;
	len = ft_lstsize(head);
	while (dist_ar[i].order < len)
	{
		j = i + 1;
		while (dist_ar[j].order < len)
		{
			if (dist_ar[i].dist < dist_ar[j].dist)
			{
				temp = dist_ar[i];
				dist_ar[i] = dist_ar[j];
				dist_ar[j] = temp;
			}
			j++;
		}
		i++;
	}
}

t_list	*get_node(t_list *objs_lst, int node_nbr)
{
	int	i;

	i = 0;
	while (i < node_nbr)
		objs_lst = objs_lst->next;
	return (objs_lst);
}

t_list	*sorted_lst(t_list *objs_lst, t_sort *ar)
{
	int	i;
	int	len;
	t_list	*new_lst;
	t_list	*node;

	i = 0;
	len = ft_lstsize(objs_lst);
	new_lst = ft_calloc(len, sizeof(t_list));
	while (i < len)
	{
		node = get_node(objs_lst, ar[i].order);
		ft_lstadd_back(&new_lst, ft_lstnew(node));
		free(node);
		i++;
	}
	return (new_lst);
}

void	sort_sprites(t_player *player, t_list *objs_lst)
{
	t_sort	*dist_ar;

	dist_ar = NULL;
	dist_ar = dist_array(objs_lst, player->pos);
	sort_array(dist_ar, objs_lst);
	/* int i = 0;
	while (i < 3)
	{
		printf("Order: %d, Dist: %f\n", dist_ar[i].order, dist_ar[i].dist);
		i++;
	}
	exit(0); */
	exit(0);
	objs_lst = sorted_lst(objs_lst, dist_ar);
	print_list(objs_lst);
	free(dist_ar);
}
