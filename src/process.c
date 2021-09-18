/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 11:45:24 by dihauet           #+#    #+#             */
/*   Updated: 2021/09/18 11:33:33 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

int			process_one(char **argv, t_parsing *list, int i)
{
	init_flag(&list->flags);
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
	init_flag(&list->flags);
	list->is_cipher = 1;
	list->flags.e = 1;
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


int         process_des(char **argv, t_parsing *list, int i)
{
	list->flags.e = 1;
	while (argv[i] && argv[i][0] == '-')
	{
		if (!(parse_flag_des(list, argv, &i)))
				return (FAILED);
		i++;
	}
	if (!list->flags.password && list->flags.key[0] == 0)
	{
			if (!(get_password(list, "enter des encryption password:")))
					return (FAILED);
	}
	if (!list->flags.i)
	{
		if (!(get_file_data(list, NULL)))
			return (FAILED);
	}
	if (list->flags.a)
			list->flags.a = 1;
  if(list->flags.hasIv == 0){
    generate_vector(list);
  }
	if (list->flags.salt[0] == 0)
	{
			generate_salt(list);
	}
	if (list->flags.key[0] == 0)
	{
			if (!(generate_key(list)))
					return (FAILED);
	}
	return (SUCCESS);
}