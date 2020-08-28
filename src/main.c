/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 12:38:35 by dihauet           #+#    #+#             */
/*   Updated: 2020/08/28 11:52:39 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

int		main(int argc, char **argv)
{
	t_parsing list;

	if (argc == 1)
		ft_ssl_usage();
	else
	{
		if (parsing_args(&list, argv, argc) == 0)
			return (0);
	}	

	/*
	** !! NE PAS OUBLIER DE FREE LE CONTENU DE LIST(list chainer,etc..)
	*/
	// while(1);
	return (0);
}