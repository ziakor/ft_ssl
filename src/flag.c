/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 12:57:37 by dihauet           #+#    #+#             */
/*   Updated: 2021/06/07 12:24:05 by dihauet          ###   ########.fr       */
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

void init_flag(t_flags *flag)
{
  flag->a = 0;
  flag->d = 0;
  flag->e = 0;
  flag->i = 0;
  flag->o = 0;
  flag->P = 0;
  flag->p = 0;
  flag->password = NULL;
  flag->q = 0;
  flag->r = 0;
  flag->s = 0;
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
    return (SUCCESS);
}

int flag_print(uint8_t key[16], uint8_t vector[16], uint8_t salt[16])
{
	if (key[0] != 0)
	{
		ft_putstr("key: ");
		ft_putnstr((char*)key, 16);
		ft_putchar('\n');
	}
  if (salt[0] != 0)
  {
    ft_putstr("salt:");
    ft_putnstr((char*)salt, 16);
    ft_putchar('\n');
  }
	if (vector[0] != 0)
	{
		ft_putstr("iv: ");
		ft_putnstr((char*)vector, 16);
	  ft_putchar('\n');
	}

  return (SUCCESS);
}