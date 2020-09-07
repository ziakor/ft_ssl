/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 12:38:35 by dihauet           #+#    #+#             */
/*   Updated: 2020/09/07 15:17:22 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

int		main(int argc, char **argv)
{
	t_parsing	list;

	if (argc == 1)
	{
		if (!(interactive_mode(&list)))
			return(0);
	}
	else
	{
		if (parsing_args(&list, argv, argc) == 0)
			return (0);
	}
	hash_data(&list);
	// read_data_list(list.list_data);
	clean_parsing(list.list_data);
	// while(1);
	return (0);
}
