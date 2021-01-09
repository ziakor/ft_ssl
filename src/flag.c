/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 12:57:37 by dihauet           #+#    #+#             */
/*   Updated: 2021/01/09 18:23:57 by dihauet          ###   ########.fr       */
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
        *i += 1;;
    }
    return (SUCCESS);
}

int flag_a(t_parsing *list)
{
    if (!(base64(list, list->list_data->data.data, list->list_data->data.data_length)))
        return (FAILED);
    free(list->list_data->data.data);
    list->list_data->data.data = list->list_data->hash.hashed_data;
    list->list_data->data.data_length = list->list_data->hash.nb_bits;
}