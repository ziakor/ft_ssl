/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 12:38:35 by dihauet           #+#    #+#             */
/*   Updated: 2021/04/05 11:05:02 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

int		main(int argc, char **argv)
{
	t_parsing	list;

	list.size = 0;
  list = (t_parsing){NULL, 0, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, NULL, NULL, NULL, NULL};
  
	if (argc == 1)
	{
    ft_ssl_usage();
		return (0);
	}
	else
	{
		if (parsing_args(&list, argv, argc) == 0)//A REVOIR
		{
			print_list_hash(list.list_data, list.flags, list.cmd, !list.is_cipher);
      list.print_func(list.list_data, list.flags, list.cmd, list.is_cipher);
			clean_parsing(&list);
			return (0);
		}
	}
	hash_data(&list);
  list.print_func(list.list_data, list.flags, list.cmd, list.is_cipher);
	clean_parsing(&list);

	return (0);
}