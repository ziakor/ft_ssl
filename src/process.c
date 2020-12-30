/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 11:45:24 by dihauet           #+#    #+#             */
/*   Updated: 2020/12/30 15:06:02 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

static int		get_option_process_one(t_flags *flags, char *str, char *cmd)
{
	if (ft_strcmp(str, "-p") == 0)
			flags->p = 1;
	else if (ft_strcmp(str, "-q") == 0)
			flags->q = 1;
	else if (ft_strcmp(str, "-r") == 0)
			flags->r = 1;
	else if (ft_strcmp(str, "-s") == 0)
			flags->s = 1;
	else
	{
		ft_invalid_option(str, cmd);
		return (FAILED);
	}
	return (SUCCESS);
}

int			process_one(char **argv, t_parsing *list, int i)
{
	while (argv[i] && argv[i][0] == '-')
	{
		if (!(get_option_process_one(&list->flags, argv[i++], list->cmd)))
			return(FAILED);
		if (list->flags.s)
			break;
	}
	if ((!argv[i] && !list->flags.s) || list->flags.p)
	{
		if (!(get_file_data(list, NULL)))
			return (FAILED);
	}
	if (list->flags.s)
	{
		if (!(get_data_s_flag(&list->list_data, argv[i++])))
			return (FAILED);
	}
	while (argv[i])
	{
		if (!(get_file_data(list, argv[i])))
			return (FAILED);
		i++;
	}
	return(SUCCESS);
}

int			process_two(char **argv, t_parsing *list, int i)
{
	list->is_cipher = 1;
	while (argv[i] && argv[i][0] == '-')
	{
		if (!(parse_flag_base64(list, argv, &i)))
			return(FAILED);
		i++;
	}
	if (!list->flags.i)
	{
		if (!(get_file_data(list, NULL)))
			return (FAILED);
	}
	return (SUCCESS);
}

int     get_password(t_parsing *list, char *prompt)
{
    if (list->flags.password = getpass(prompt))
        return (FAILED);
}

int         process_des(char **argv, t_parsing *list, int i)
{
    while (argv[i] && argv[i][0] == '-')
    {
        if (!(parse_flag_des(list, argv, &i)))
            return (FAILED);
        i++;
    }
    if (!list->flags.password)
    {
        if (!(get_password(list, "enter des-cbc encryption password:")))
            return (FAILED);
    }
    printf("DES\n");
    exit(0);
    if (!list->flags.i)
	{
		if (!(get_file_data(list, NULL)))
			return (FAILED);
	}

}