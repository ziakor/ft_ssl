/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_read_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 11:07:11 by dihauet           #+#    #+#             */
/*   Updated: 2020/11/04 11:08:14 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

char	*free_read_data_list(t_list *list)
{
	t_list *tmp;

	if (list)
	{
		while (list)
		{
			tmp = list->next;
			if (list->content)
				free(list->content);
			free(list);
			list = tmp;
		}
	}
	return (NULL);
};

t_list		*ft_lst_add_data_to_end(t_list *list, char *data, int size)
{
	t_list *head;
	t_list *new_elem;

	if (!(new_elem = (t_list*) malloc(sizeof(t_list))))
	{
		free(data);
		return (NULL);
	}
	new_elem->content = (char*)data;
	new_elem->content_size = size;
	new_elem->next = NULL;
	if (list)
	{
	head = list;
	while (list->next)
		list = list->next;
	list->next = new_elem;
	}
	else
		head = new_elem;
	return(head);
}