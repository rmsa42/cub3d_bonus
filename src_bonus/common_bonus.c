/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 00:48:27 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/21 00:50:02 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	elim_obj(t_list **head, t_list *elim_obj)
{
	t_list	*temp;

	temp = *head;
	if (*head == elim_obj)
	{
		*head = elim_obj->next;
		free(elim_obj->content);
		free(elim_obj);
		return ;
	}
	while (temp->next && temp->next != elim_obj)
		temp = temp->next;
	if (temp->next == NULL)
		return ;
	temp->next = elim_obj->next;
	free(elim_obj->content);
	free(elim_obj);
	elim_obj = NULL;
}
