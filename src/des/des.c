/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:50:18 by dihauet           #+#    #+#             */
/*   Updated: 2021/02/03 15:59:06 by dihauet          ###   ########.fr       */
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

// int     des_cbc(t_parsing *list, unsigned char *str, size_t length)
// {
//     t_des des;
//     create_key_des_ecb(list, &des);

//     if (list->flags.e)
//     {
//         if (!(des_cbc_encode(list, &des, str, length)))
//             return (FAILED);
//     }
//     else
//     {
//         if (!(des_cbc_decode(list, &d)))
//     }
// }
// |47||56||115||56||81||110||86||117||54||50||97||43||51||88||67||107||120||115||121||84||49||119||61||61|
