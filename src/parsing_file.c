/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 10:56:43 by dihauet           #+#    #+#             */
/*   Updated: 2021/01/07 17:31:04 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

char		*read_file_data(int fd, int *size)
{
	t_list 	*list;
	char	*buffer;
	int		ret;

	if (!(buffer = (char*)malloc(sizeof(char) * 32000000)))
		return (NULL);
	list = NULL;
	while ((ret = read(fd, buffer, 32000000)) > 0)
	{
		*size = *size + ret;
		if (!(list = ft_lst_add_data_to_end(list, buffer, ret)))
			return (free_read_data_list(list));
	if (!(buffer = (char*)malloc(sizeof(char) * 32000000)))
		return (free_read_data_list(list));
	}
	if (buffer)
		free(buffer);
	if (ret < 0)
		return (free_read_data_list(list));
	return(concat_list_to_str(list, *size));
}
int 		get_file_data(t_parsing *list, char *filename)
{
	char *data;
	t_list_data *new_elem;
	int fd;

	list->size = 0;
	data = NULL;
	fd = 0;
	if (filename  && (fd = open_file(filename)) < 0)
	{
		data = get_error_message_open_file(fd, &list->size);
	}
	else
	{
		if (!(data = read_file_data(fd, &list->size)))
			return (FAILED);
	}
	if (!(new_elem = create_new_elem(data, filename ? filename : "stdin", fd, list->size)))
		return (FAILED);
	if (fd >= 0)
		free(data);
	add_new_elem(&(list->list_data),new_elem);
	return (SUCCESS);
}

char		*concat_list_to_str(t_list *list, int size)
{
	char *str;
	int pos;
	t_list *tmp;
	pos = 0;
	if (!(str = (char*)malloc(sizeof(char) * size)))
		return (NULL);
	while (list)
	{
		ft_memcpy(str + pos,list->content,list->content_size);
		tmp = list->next;
		free(list->content);
		free(list);
		list = tmp;
	}
	return(str);
}

