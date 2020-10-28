/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 11:45:24 by dihauet           #+#    #+#             */
/*   Updated: 2020/10/28 17:06:27 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

static int		get_option_process_one(t_flags *flags, char *str)
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
		return (FAILED);
	return (SUCCESS);
}
int 		get_file_data(t_parsing *list, char *argv)
{
	char *data;


}

int			process_one(char **argv, t_parsing *list)
{
	int i;

	i = 2;
	printf("%s\n", argv[i]);
	while (argv[i] && argv[i][0] == '-')
	{
		if (!(get_option_process_one(&list->flags,argv[i])))
		{	
			printf("ASD\n");
			return(FAILED);
		}
		i++;
		if (list->flags.s)
			break;
	}
	if ((!argv[i] && !list->flags.s) || list->flags.p)
		printf("SALSIFI");
	if (list->flags.s)
	{
		if (!(get_data_s_flag(&list->list_data, argv[i])))
			return (FAILED);
		i++;
	}
	while (argv[i])
	{
		if (!(get_file_data(list, argv[i])))
			return (FAILED);
		i++;
	}
	return(SUCCESS);
}