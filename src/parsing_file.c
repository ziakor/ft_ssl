/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 10:56:43 by dihauet           #+#    #+#             */
/*   Updated: 2021/09/13 15:02:40 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

unsigned char		*read_file_data(int fd, int *size)
{
	t_list 	*list;
	unsigned char	*buffer;
	int		ret;

	if (!(buffer = (unsigned char*)malloc(sizeof( unsigned char) * 32000)))
		return (NULL);
	list = NULL;

	while ((ret = read(fd, buffer, 32000)) > 0)
	{
		*size = *size + ret;
		if (!(list = ft_lst_add_data_to_end(list, (char*)buffer, ret)))
			return ((unsigned char*)free_read_data_list(list));
	if (!(buffer = (unsigned char*)malloc(sizeof(unsigned char) * 32000)))
		return ((unsigned char*)free_read_data_list(list));
	}
	if (buffer)
		free(buffer);
	if (ret < 0)
		return ((unsigned char*)free_read_data_list(list));
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
		if (!(data = (char*)read_file_data(fd, &list->size)))
			return (FAILED);
	}
	if (!(new_elem = create_new_elem(data, filename ? filename : "stdin", fd, list->size)))
		return (FAILED);
	if (fd >= 0)
		free(data);
	add_new_elem(&(list->list_data),new_elem);

	return (SUCCESS);
}

unsigned char *concat_list_to_str(t_list *list, int size)
{
	unsigned char *str;
	int pos;
	t_list *tmp;
    size_t i;

    i = 0;
	pos = 0;
	if (!(str = (unsigned char*)malloc(sizeof(unsigned char) * size)))
		return (NULL);

	while (list)
	{
		tmp = list->next;
    while (i < list->content_size)
    {
        str[pos] = ((unsigned char*)list->content)[i];
        i++;
        pos++;
    }
    i = 0;
    if (list->content)
		  free(list->content);
		if (list)
      free(list);
		list = tmp;
	}
	return(str);
}

