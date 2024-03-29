/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:49:59 by dihauet           #+#    #+#             */
/*   Updated: 2021/09/17 12:08:44 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

int flag_salt(t_parsing *list, char **argv, int *i)
{
	t_list_data *new_elem;
	int j;
	int len;
	
	j = 0;
	new_elem = NULL;
	*i+=1;
	if (!argv[*i])
	{
		if (!(new_elem = create_new_elem("Option \'-k\' need a value", "ft_ssl", -1, 24)))
			return (FAILED);
		add_new_elem(&list->list_data, new_elem);
	}
	else
	{
		len = ft_strlen(argv[*i]);
		while (j < 16)
		{
			if (j < len)
			{
				if (!ft_is_hexa(argv[*i][j]))
				{
					if (!(new_elem = create_new_elem("invalid hex key value", "ft_ssl", -1, 22)))
						return (FAILED);
					add_new_elem(&list->list_data, new_elem);
					return (FAILED);
				}
				list->flags.salt[j] = argv[*i][j] >= 'a' && argv[*i][j] <= 'z' ? ft_toupper(argv[*i][j]) : argv[*i][j];
			}
			else
				list->flags.salt[j] = '0';
			j++;
		}
		if (len > 16)
			write(2, "hex string is too long ignoring excess\n", 39);
	}
	return (SUCCESS);
}

int flag_vector(t_parsing *list, char **argv, int *i)
{
	t_list_data *new_elem;
	int j;
	int len;
	
	j = 0;
	new_elem = NULL;
	*i += 1;
	if (!argv[*i])
	{
		if (!(new_elem = create_new_elem("Option \'-v\' need a value", "ft_ssl", -1, 24)))
			return (FAILED);
		add_new_elem(&list->list_data, new_elem);
	}
	else
	{
		len = ft_strlen(argv[*i]);
		while (j < 16)
		{
			if (j < len)
			{
				if (!ft_is_hexa(argv[*i][j]))
				{
					if (!(new_elem = create_new_elem("invalid hex key value", "ft_ssl", -1, 22)))
						return (FAILED);
					add_new_elem(&list->list_data, new_elem);
					return (FAILED);
				}
				list->flags.vector[j] = argv[*i][j] >= 'a' && argv[*i][j] <= 'z' ? argv[*i][j] - 32 : argv[*i][j];
			}
			else
				list->flags.vector[j] = '0';
			j++;
		}
		if (len > 16)
			write(1, "hex string is too long ignoring excess\n", 39);
	}
	return (SUCCESS);
}

int flag_key(t_parsing *list, char **argv, int *i)
{
	t_list_data *new_elem;
	int j;
	int len;
	
	j = 0;
	new_elem = NULL;
	*i+=1;
	if (!argv[*i])
	{
		if (!(new_elem = create_new_elem("Option \'-k\' need a value", "ft_ssl", -1, 24)))
			return (FAILED);
		add_new_elem(&list->list_data, new_elem);
	}
	else
	{
		len = ft_strlen(argv[*i]);
		while (j < 16)
		{
			if (j < len)
			{
				if (!ft_is_hexa(argv[*i][j]))
				{
					if (!(new_elem = create_new_elem("invalid hex key value", "ft_ssl", -1, 22)))
						return (FAILED);
					add_new_elem(&list->list_data, new_elem);
					return (FAILED);
				}
				list->flags.key[j] = argv[*i][j] >= 'a' && argv[*i][j] <= 'z' ? ft_toupper(argv[*i][j]) : argv[*i][j];
			}
			else
				list->flags.key[j] = '0';
			j++;
		}
		if (len > 16)
			write(2, "hex string is too long ignoring excess\n", 39);
	}
	return (SUCCESS);
}

int flag_password(t_parsing *list, char **argv, int *i)
{
	*i += 1;

	if (!argv[*i])
	{
    free(list->list_data->data.data);
    free(list->list_data->data.file_name);
    if (!(list->list_data->data.data = (unsigned char*)ft_strdup("Option \'-p\' need a value")))
      return(FAILED);
    list->list_data->data.fd = -1;
    list->list_data->data.data_length = 24;
    if (!(list->list_data->data.file_name = ft_strdup(list->cmd)))
    {
      return (FAILED);
    }
		return (FAILED);
	}
	else
	{
    list->flags.password = argv[*i];
	}
	return (SUCCESS);
}



int			parse_flag_des(t_parsing *list, char **argv, int *i)
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
	else if (ft_strcmp(argv[*i], "-a") == 0)
	{
		list->flags.a = 1;
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
	else if (ft_strcmp(argv[*i], "-p") == 0)
	{
		if (!(flag_password(list,argv,i)))
			return(FAILED);
	}
    else if (ft_strcmp(argv[*i], "-P") == 0)
    {
        list->flags.P = 1;
    }
	else if (ft_strcmp(argv[*i], "-k") == 0)
	{
    list->flags.hasKey = 1;
		if (!(flag_key(list,argv,i)))
			return(FAILED);
	}
	else if (ft_strcmp(argv[*i], "-s") == 0)
	{
    list->flags.hasSalt = 1;
		if (!(flag_salt(list,argv,i)))
			return(FAILED);
	}
    else if (ft_strcmp(argv[*i], "-v") == 0)
    {
        list->flags.hasIv= 1;
        if (!(flag_vector(list, argv, i)))
            return (FAILED);
    }
    else
        return (ft_invalid_option(argv[*i], list->cmd, ft_list_options_des));
    return (SUCCESS);
}