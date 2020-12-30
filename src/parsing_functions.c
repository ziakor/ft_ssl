/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 13:27:13 by dihauet           #+#    #+#             */
/*   Updated: 2020/12/27 17:54:26 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

int		open_file(char *file_name)
{
	int		fd;

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
	if (!data)
	{
		if (!(elem = create_new_elem("Wrong option used \'-s\'", "ft_ssl", -1, 22)))
			return (FAILED);
	}
	else
	{
	if (!(elem = create_new_elem(data, data, 1, ft_strlen(data))))
		return (FAILED);
	}
	add_new_elem(list_data, elem);
	return (SUCCESS);
}
