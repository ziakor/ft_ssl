/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:50:18 by dihauet           #+#    #+#             */
/*   Updated: 2021/01/22 16:00:57 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"
#include <inttypes.h>

int		des_ecb(t_parsing *list, char *str, size_t length)
{
    t_des des;
    create_key_des_ecb(list, &des);
    if(list->flags.e)
    {
        if (!(des_ecb_encode(list, &des, str, length)))
            return (FAILED);
    }
    // uint64_t t = hex_to_uint64(list->flags.key);
    write(1,list->list_data->hash.hashed_data, list->list_data->hash.nb_bits);
	exit(0);
	return (SUCCESS);
}
