/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:14:57 by dihauet           #+#    #+#             */
/*   Updated: 2021/04/04 14:08:09 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

void	clean_parsing(t_parsing *list)
{
	t_list_data *tmp;

	tmp = NULL;
	
	if (list->flags.o_file)
		free(list->flags.o_file);
  if (list->flags.password)
      free(list->flags.password);
	while (list->list_data)
	{
		tmp = list->list_data->next;
		if (list->list_data->data.data)
			free(list->list_data->data.data);
		if (list->list_data->data.file_name)
			free(list->list_data->data.file_name);
		if (list->list_data->data.fd > 2)
			close(list->list_data->data.fd);
		if (list->list_data->hash.hashed_data)
			free(list->list_data->hash.hashed_data);
    if (list->list_data)
    {
      free(list->list_data);
      list->list_data = NULL;
    }
		list->list_data = tmp;
	}
}
