/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 12:57:37 by dihauet           #+#    #+#             */
/*   Updated: 2021/04/04 17:37:45 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"


int flag_input(t_parsing *list, char **argv, int *i)
{
		t_list_data *new_elem;
		new_elem = NULL;
		list->flags.i = 1;
		
		if (!(argv[++*i]))
		{
				if (!(new_elem = create_new_elem("Option \'-i\' need a value", "ft_ssl", -1, 24)))
						return(FAILED);
				add_new_elem(&list->list_data, new_elem);
				return(FAILED);
		}
		else
		{
				if (!(get_file_data(list, argv[*i])))
						return (FAILED);
		}
		return (SUCCESS);
}

int flag_output(t_parsing *list, char **argv, int *i)
{
		t_list_data *new_elem;
		new_elem = NULL;
		list->flags.o = 1;
		if (list->flags.o_file)
				free(list->flags.o_file);
		if (!(argv[++*i]))
		{
				if (!(new_elem = create_new_elem("Option \'-o\' need a value", "ft_ssl", -1, 24)))
			return (FAILED);
				add_new_elem(&list->list_data, new_elem);
				return(FAILED);
		}
		else
		{
				if (!(list->flags.o_file = ft_strdup(argv[*i])))
						return(FAILED);
		}
		return (SUCCESS);
}

int flag_a(t_parsing *list)
{
		if (!(base64(list, list->list_data->data.data, list->list_data->data.data_length)))
				return (FAILED);
		free(list->list_data->data.data);
		list->list_data->data.data = NULL;
		list->list_data->data.data = list->list_data->hash.hashed_data;
		list->list_data->hash.hashed_data = NULL;
		list->list_data->data.data_length = list->list_data->hash.nb_bits;
}

int flag_print(uint8_t key[16], uint8_t vector[16])
{
	if (key[0] != 0)
	{
		ft_putstr("key: ");
		ft_putnstr(key, 16);
		ft_putchar('\n');
	}
	if (vector[0] != 0)
	{
		ft_putstr("iv: ");
		ft_putnstr(vector, 16);
	}
	ft_putchar('\n');
}