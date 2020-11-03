/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 11:45:24 by dihauet           #+#    #+#             */
/*   Updated: 2020/11/03 15:49:19 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

static int		get_option_process_one(t_flags *flags, char *str)
{
	if (ft_strcmp(str, "-p") == 0)
			flags->p = 1;
	else if (ft_strcmp(str, "-q") == 0)
			flags->q = 1;
	else if (ft_strcmp(str, "-r") == 0)
			flags->r = 1;
	else if (ft_strcmp(str, "-s") == 0)
			flags->s = 1;
	else
		return (FAILED);
	return (SUCCESS);
}
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
}

char		*read_file_data(int fd, int *size)
{
	t_list 	*list;
	t_list *new_elem;
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
		return (NULL);
	}
	if (buffer)
		free(buffer);
	if (ret < 0)
	{
		return (NULL);
	}
	return(concat_list_to_str(list, *size));
}
int 		get_file_data(t_parsing *list, char *filename)
{
	char *data;
	t_list_data *new_elem;
	int fd;

	data = NULL;
	
	if ((fd = open_file(filename)) < 0)
	{
		data = get_error_message_open_file(fd, &list->size);
	}
	else
	{
		if (!(data = read_file_data(fd, &list->size)))
			return (FAILED);
	}
	if (!(new_elem = create_new_elem(data, filename, fd, list->size)))
		return (FAILED);
	if (fd >= 0)
		free(data);
	add_new_elem(&(list->list_data),new_elem);
	return (SUCCESS);
	


}

int			process_one(char **argv, t_parsing *list)
{
	int i;

	i = 2;
	while (argv[i] && argv[i][0] == '-')
	{
		if (!(get_option_process_one(&list->flags,argv[i])))
		{
			return(FAILED);
		}
		i++;
		if (list->flags.s)
			break;
	}
	if ((!argv[i] && !list->flags.s) || list->flags.p)
		printf("SALSIFI");
	if (list->flags.s)
	{
		if (!(get_data_s_flag(&list->list_data, argv[i])))
			return (FAILED);
		i++;
	}
	while (argv[i])
	{
		if (!(get_file_data(list, argv[i])))
			return (FAILED);
		i++;
	}
	return(SUCCESS);
}