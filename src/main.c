/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 12:38:35 by dihauet           #+#    #+#             */
/*   Updated: 2020/11/14 03:19:00 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

int		main(int argc, char **argv)
{
	t_parsing	list;

	list.size = 0;
	if (argc == 1)
	{
		if (!(interactive_mode(&list)))
		{
			print_list_hash(list.list_data, list.flags, list.cmd, !list.is_cipher);
			clean_parsing(&list);
			return (0);
		}
			
	}
	else
	{
		if (parsing_args(&list, argv, argc) == 0)
		{
			printf("%d %d %d %d", list.flags.d, list.flags.e,list.flags.i, list.flags.o);
			print_list_hash(list.list_data, list.flags, list.cmd, !list.is_cipher);
			clean_parsing(&list);
			return (0);
		}
	}
	if (!list.is_cipher)
		hash_data(&list);
	print_list_hash(list.list_data, list.flags, list.cmd, !list.is_cipher);
	clean_parsing(&list);

	int i = 0;
	return (0);
}
