/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 10:44:11 by dihauet           #+#    #+#             */
/*   Updated: 2021/01/22 15:14:47 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

uint64_t    ecb_get_64bit(char *data, int bit)
{
    int i;
    uint64_t ret;
    int pad;
    pad = 0;
    i = 0;
    ret = 0;
    while (i < 8)
    {
        ret <<= 8;
        if (pad == 0)
        {
            if (data[i])
                ret |= data[i];
            else
            {
                pad = 1;
                ret |= bit;
            }
        }
        else
            ret |= bit;
        i++;
    }
    return (ret);
}