/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 13:27:13 by dihauet           #+#    #+#             */
/*   Updated: 2020/10/07 20:47:11 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

int		get_option(t_flags *flags, char c)
{
	if (c == 'q')
		flags->q = 1;
	else if (c == 'p')
		flags->p = 1;
	else if (c == 'r')
		flags->r = 1;
	else if (c == 's')
		flags->s = 1;
	else
		return (FAILED);
	return (SUCCESS);
}

char	*read_stdin(int *count)
{
	char	*tmp;
	char	*stdin_data;
	char	buffer[1001];
	int		ret;

	if (!(stdin_data = (char*)malloc(sizeof(char))))
		return (NULL);
	stdin_data[0] = '\0';
	while ((ret = read(0, buffer, 1000)) > 0)
	{
		*count = *count + ret;
		tmp = ft_strjoin_size(stdin_data, buffer, *count - ret, ret);
		free(stdin_data);
		stdin_data = tmp;
	}
	if (ret == -1)
		return (NULL);
	return (stdin_data);
}

char	*read_file(int fd, int *count)
{
	char	*tmp;
	char	*file_data;
	char	buffer[1001];
	int		ret;

	if (!(file_data = (char*)malloc(sizeof(char))))
		return (NULL);
	file_data[0] = '\0';
	while ((ret = read(fd, buffer, 1000)) > 0)
	{
		*count = *count + ret;
		tmp = ft_strjoin_size(file_data, buffer, *count - ret, ret);
		free(file_data);
		file_data = tmp;
	}
	if (ret == -1)
		return (NULL);
	return (file_data);
}

int		open_file(char *file_name, char *cmd)
{
	int		fd;

	(void)cmd;
	fd = 0;
	if ((fd = open(file_name, O_DIRECTORY)) != -1)
	{
		return (-2);
	}
	if ((fd = open(file_name, O_RDONLY)) == -1)
		return (-1);
	return (fd);
}

int		get_data_s_flag(t_list_data **list_data, char *data)
{
	t_list_data *elem;

	elem = NULL;
	if (!(elem = create_new_elem(data, data, 2, ft_strlen(data))))
	{
		return (FAILED);
	}
	add_new_elem(list_data, elem);
	return (SUCCESS);
}
