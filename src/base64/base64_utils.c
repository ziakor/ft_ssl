/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 15:26:33 by dihauet           #+#    #+#             */
/*   Updated: 2021/02/01 16:43:38 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

int			parse_flag_base64(t_parsing *list, char **argv, int *i)
{
	if (ft_strcmp(argv[*i], "-d") == 0)
	{
		list->flags.d = 1;
		list->flags.e = 0;
	}
	else if (ft_strcmp(argv[*i], "-e") == 0)
    {
		list->flags.e = 1;
		list->flags.d = 0;
    }
    else if (ft_strcmp(argv[*i], "-i") == 0)
	{
		if (!(flag_input(list, argv, i)))
            return (FAILED);
	}
	else if (ft_strcmp(argv[*i], "-o") == 0)
	{
        if (!(flag_output(list,argv,i)))
            return(FAILED);
	}
	else
	{
		ft_invalid_option(argv[*i], list->cmd, ft_list_options_base64);
		return (FAILED);
	}
	return (SUCCESS);
}