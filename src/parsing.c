/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 18:59:35 by dihauet           #+#    #+#             */
/*   Updated: 2020/11/06 15:10:25 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

int		get_options(t_flags *flags, char **argv, int *position_argv, int i)
{
	*position_argv = *position_argv + 1;
	while (argv[*position_argv] && argv[*position_argv][0] == '-')
	{
		i = 1;
		if (get_option(flags, argv[*position_argv][1]) == 0)
			return (FAILED);
		
		*position_argv = *position_argv + 1;
		if (flags->s)
			break ;
	}
	return (SUCCESS);
}


int		process_commands(char **argv, t_parsing *list)
{
	int i;

	i = 2;
	if (!(list->process_func(argv, list, 2)))
		return(FAILED);
	return (SUCCESS);
}

int		parsing_args(t_parsing *list, char **argv, int argc)
{
	int	i;
	int	position_argv;

	argc++;
	i = 0;
	position_argv = 1;
	while (g_all_cmd[i].cmd != NULL)
	{
		if (ft_stricmp(g_all_cmd[i].cmd, argv[position_argv]) == 0)
		{
			*list = g_all_cmd[i];
			if (!(process_commands(argv, list)))
				return (FAILED);
			return (SUCCESS);
		}
		i++;
	}
	ft_invalid_command(argv[1]);
	return (FAILED);
}
