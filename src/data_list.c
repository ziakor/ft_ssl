/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 10:56:05 by dihauet           #+#    #+#             */
/*   Updated: 2020/08/28 11:48:23 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

t_list_data *create_new_elem(char *str, char *file_name, int fd)
{
	t_list_data *new_elem;

	new_elem = NULL;

	if (!(new_elem = (t_list_data*)malloc(sizeof(t_list_data))))
		return (NULL);
	
	new_elem->data.data = str;
	new_elem->data.data_length = ft_strlen(new_elem->data.data);
	new_elem->data.file_name = file_name;
	new_elem->data.fd = fd;
	return (new_elem);
}

t_list_data *add_new_elem(t_list_data *list, t_list_data *new_elem)
{
	t_list_data *head;

	head = list;

	while (list->next)
	{
		list = list->next;
	}
	list->next = new_elem;

	return head;
}