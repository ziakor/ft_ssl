/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 15:55:54 by dihauet           #+#    #+#             */
/*   Updated: 2020/09/13 16:52:48 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

int		hash_data(t_parsing *list)
{
	t_list_data *head;

	head = list->list_data;
	while (list->list_data)
	{
		if (list->list_data->data.fd >= 0)
			list->hash_func(&list->list_data->hash, list->list_data->data.data,
			list->list_data->data.data_length);
		list->list_data = list->list_data->next;
	}
	list->list_data = head;
	return (1);
}
