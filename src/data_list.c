/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 10:56:05 by dihauet           #+#    #+#             */
/*   Updated: 2020/09/02 20:55:59 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

t_list_data	*create_new_elem(char *str, char *file_name, int fd)
{
	t_list_data	*new_elem;

	new_elem = NULL;
	if (!(new_elem = (t_list_data*)malloc(sizeof(t_list_data))))
		return (NULL);
	if (!(new_elem->data.data = ft_strdup(str)))
		return (NULL);
	if (!(new_elem->data.file_name = ft_strdup(file_name)))
		return (NULL);
	new_elem->data.fd = fd;
	new_elem->next = NULL;
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
	printf("ASDASDASDASD\n");
	while (list)
	{
		ft_putstr("ELEM\n");
		ft_putstr(list->data.file_name);
		ft_putchar('\n');
		ft_putstr(list->data.data);
		list = list->next;
		ft_putstr("\n--------\n");
	}
}
