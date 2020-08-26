/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 18:59:35 by dihauet           #+#    #+#             */
/*   Updated: 2020/08/26 19:24:09 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

int get_option(t_flags *flags, char c)
{
	if (c == 'q')
		flags->q = 1;
	else if (c == 'p')
		flags->p = 1;
	else if (c == 'r')
		flags->r = 1;
	else if (c == 's')
		flags->s = 1;
	else
		return (0);
	return (1);
}

int get_options(t_flags *flags, char **argv, int *position_argv)
{
	int size;
	int i ;
	*position_argv = *position_argv + 1;
	while (argv[*position_argv] && argv[*position_argv][0] == '-')
	{
		i = 1;
		size = ft_strlen(argv[*position_argv]);
		if (size > 2)
		{
			while (argv[*position_argv][i])
			{
				if (get_option(flags, argv[*position_argv][i]) == 0)
					return (0);
				i++;
			}
		}
		else
		{
			if (get_option(flags, argv[*position_argv][1]) == 0)
				return (0);
		}
		*position_argv = *position_argv + 1;

	}
	return (1);
}

int read_stdin()
{
	char *tmp;
	char *stdin_data;
	char str[101];
	int length;
	int ret;
	
	length = 0;
	str[100] = '\0';
	if (!(stdin_data = (char*)malloc(sizeof(char) * 101)))
		return (-1);
	stdin_data[0]  = '\0';
	while ((ret = read(0, str, 100)) > 0)
	{
		str[ret] = '\0';
		tmp = ft_strjoin(stdin_data, str);
		free(stdin_data);
		stdin_data = tmp;
	}
	printf("%s\n", stdin_data);
	if (ret == -1)
		return (-1);

	return(1);
}


int get_data(t_parsing *list, char **argv, int argc)
{
	int i;

	i = 0;
	printf("%s\n", argv[0]);
	printf(">>%d\n", argc);
	
	if (argc == 0 || list->flags.p == 1)
		read_stdin();

	// while (i < argc)
	// {

	// }
	return (1);
}

int parsing_args(t_parsing *list, char **argv, int argc)
{
	int i;
	int position_argv;
	
	argc++;
	i = 0;
	position_argv = 1;
	while(g_all_cmd[i].cmd != NULL)
	{
		if(ft_strcmp(g_all_cmd[i].cmd, argv[position_argv]) == 0)
		{
			*list = g_all_cmd[i];
			if (get_options(&list->flags,argv, &(position_argv)) == 0)
				return (ft_invalid_option(argv[position_argv], list->cmd));
			get_data(list,argv + position_argv, argc - position_argv - 1);
			return (1);
		}
		i++;
	}
	ft_invalid_command(argv[1]);
	return(0);
}