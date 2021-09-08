/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 18:59:35 by dihauet           #+#    #+#             */
/*   Updated: 2021/09/08 11:34:48 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

int		process_commands(char **argv, t_parsing *list)
{
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
				return (0);
			return (1);
		}
		i++;
	}
  if (!ft_strcmp(argv[1], "help"))
  {
    ft_ssl_help();
  }
	else {
    ft_invalid_command(argv[1]);
  }
	return (0);
}
