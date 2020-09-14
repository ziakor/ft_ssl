/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:14:57 by dihauet           #+#    #+#             */
/*   Updated: 2020/09/14 14:02:21 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

void	clean_parsing(t_list_data *list_data)
{
	t_list_data *tmp;

	tmp = NULL;
	while (list_data)
	{
		tmp = list_data->next;
		if (list_data->data.data)
			free(list_data->data.data);
		if (list_data->data.file_name)
			free(list_data->data.file_name);
		if (list_data->data.fd > 2)
			close(list_data->data.fd);
		if (list_data->hash.hashed_data)
			free(list_data->hash.hashed_data);
		free(list_data);
		list_data = tmp;
	}
}
