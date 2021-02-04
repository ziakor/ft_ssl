/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:50:18 by dihauet           #+#    #+#             */
/*   Updated: 2021/02/04 09:55:53 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"
#include <inttypes.h>

int		des_ecb(t_parsing *list, unsigned char *str, size_t length)
{
    t_des des;
    create_key_des_ecb(list, &des);

    if(list->flags.e)
    {
        if (!(des_ecb_encode(list, &des, str, length)))
            return (FAILED);
    }
    else
    {
        if (!(des_ecb_decode(list, &des, str, length)))
            return (FAILED);
    }
	return (SUCCESS);
}

