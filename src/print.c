/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 15:16:37 by dihauet           #+#    #+#             */
/*   Updated: 2020/09/18 13:30:07 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

void	print_list_hash(t_list_data *list, t_flags flags, char *cmd)
{
	if (flags.p)
	{
		ft_putstr(list->data.data);
		if (list->data.data[list->data.data_length - 1] != '\n')
			ft_putchar('\n');
	}
	while (list)
	{
		if (list->data.fd < 0)
			print_error(list->data.data, list->data.file_name);
		else if (flags.q)
		{
			print_hash_data(list->hash.hashed_data, list->hash.nb_words);
			ft_putchar('\n');
		}
		else if (flags.r)
			print_reverse_hash(list->hash, list->data.file_name);
		else
			print_hash(list->hash, cmd, list->data.file_name);
		list = list->next;
	}
}
