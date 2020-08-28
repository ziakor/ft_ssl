/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 18:59:35 by dihauet           #+#    #+#             */
/*   Updated: 2020/08/28 13:54:07 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"



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





char *read_file(t_parsing *list, char* file_name)
{
	char *tmp;
	char *file_data;
	char *str[1000];
	int ret;

	if (!(file_data = (char*)malloc(sizeof(char))))
		return (NULL);
	file_data[0] = '\0';
}



int get_data(t_parsing *list, char **argv, int argc)
{
	int i;
	char *data;
	i = 0;
	
	data = NULL;
	if (argc == 0 || list->flags.p == 1)
	{
		if (!(data = get_stdin()))
			return (0);
		if (!(list->list_data = create_new_elem(data, "STDIN", 0)))
			return (0);
		printf("%s\n", list->list_data->data.data);
	}
	while (i < argc)
	{
		if (!(read_file(list, argv[i])))
			return (0);
		i++;
	}
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