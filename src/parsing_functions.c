/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 13:27:13 by dihauet           #+#    #+#             */
/*   Updated: 2020/08/28 14:02:58 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

int get_option(t_flags *flags, char c)
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
		return (0);
	return (1);
}

char *get_stdin()
{
	char *tmp;
	char *stdin_data;
	char str[1000];
	int ret;
	
	if (!(stdin_data = (char*)malloc(sizeof(char))))
		return (NULL);
	stdin_data[0]  = '\0';
	while ((ret = read(0, str, 1000)) > 0)
	{
		str[ret] = '\0';
		tmp = ft_strjoin(stdin_data, str);
		free(stdin_data);
		stdin_data = tmp;
	}
	if (ret == -1)
		return (NULL);
	return(stdin_data);
}

int open_file(char *file_name, char *cmd)
{
	int fd;

	fd = 0;
	if ((fd = open(file_name, O_DIRECTORY)) != -1)
	{
		return (-2);
	}
	if ((fd = open(file_name, O_RDONLY)) == -1)
		return (-1);
	return (fd);
}

char *get_error_message_open_file(int type)
{
	if (type == -1)
		return (strerror(errno));
	else if (type == -2)
		return ("Is a directory");
}