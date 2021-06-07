/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 10:56:05 by dihauet           #+#    #+#             */
/*   Updated: 2021/06/07 10:54:38 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

t_list_data	*create_new_elem(char *str, char *file_name, int fd, int size_data)
{
	t_list_data		*new_elem;
	int				i;

	i = -1;
	new_elem = NULL;
	if (!(new_elem = (t_list_data*)malloc(sizeof(t_list_data))))
		return (NULL);
	if (!(new_elem->data.data = (unsigned char*)malloc(sizeof(unsigned char) * size_data)))
		return (NULL);
	while (++i < size_data)
		new_elem->data.data[i] = str[i];
	if (!(new_elem->data.file_name = ft_strdup(file_name)))
		return (NULL);
	new_elem->data.data_length = size_data;
	new_elem->data.fd = fd;
	new_elem->next = NULL;
	new_elem->hash.hashed_data = NULL;
	return (new_elem);
}

void		add_new_elem(t_list_data **list, t_list_data *new_elem)
{
	t_list_data *last;

	last = *list;
	if (*list == NULL)
	{
		*list = new_elem;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_elem;
}

void		read_data_list(t_list_data *list)
{
	while (list)
	{
		ft_putstr("ELEM\n");
		ft_putstr((const char*)list->data.file_name);

    
		ft_putchar('\n');
		ft_putstr((const char*)list->data.data);

		list = list->next;
		ft_putstr("\n--------\n");
	}
}
