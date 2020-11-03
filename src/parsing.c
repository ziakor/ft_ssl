/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 18:59:35 by dihauet           #+#    #+#             */
/*   Updated: 2020/11/02 18:26:06 by dihauet          ###   ########.fr       */
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

char	*get_file(t_parsing *list, char *file_name)
{
	char		*file_data;
	t_list_data	*new_elem;
	int			fd;

	list->size = 0;
	new_elem = NULL;
	if ((fd = open_file(file_name)) < 0)
	{
		file_data = get_error_message_open_file(fd, &list->size);
	}
	else
	{
		if (!(file_data = read_filee(fd, &list->size)))
			return (NULL);
	}
	if (!(new_elem = create_new_elem(file_data, file_name, fd, list->size)))
		return (NULL);
	if (new_elem->data.fd >= 0)
		free(file_data);
	add_new_elem(&(list->list_data), new_elem);
	return (file_data);
}

int		get_data(t_parsing *list, char **argv, int argc)
{
	int		i;
	char	*data;

	i = 0;
	data = NULL;
	if (argc == 0 || list->flags.p == 1)
	{
		if (!(data = read_stdin(&list->size)))
			return (FAILED);
		if (!(list->list_data = create_new_elem(data, "stdin", 0, list->size)))
			return (FAILED);
		free(data);
		data = NULL;
	}
	if (list->flags.s)
	{
		if (!(get_data_s_flag(&list->list_data, argv[i++])))
			return (FAILED);
	}
	while (i < argc)
	{
		if (!(data = get_file(list, argv[i++])))
			return (FAILED);
	}
	return (SUCCESS);
}

int		process_commands(char **argv, t_parsing *list)
{
	int i;

	i = 2;
	if (!(list->process_func(argv,list)))
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
				return (ft_invalid_option(argv[position_argv], list->cmd));
			return (SUCCESS);
		}
		i++;
	}
	ft_invalid_command(argv[1]);
	return (FAILED);
}
