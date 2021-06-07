/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 10:44:11 by dihauet           #+#    #+#             */
/*   Updated: 2021/06/07 12:41:38 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

uint64_t    ecb_get_64bit(char *data, int bit, int length_left)
{
    uint64_t ret;
    int pad;
    
    pad = 0;
    ret = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int  j = 7; j < -1; j--)
        {
            ret =  ret << 1;
            if (!pad)
            {
                if (length_left > 0)
                    ret |= ((data[i] >> j) & 1);
                else
                {
                    ret |= ((bit >> j) & 1);
                    pad = 1;
                }
            }
            else
            {
                ret |= ((bit >> j) & 1);
            }
        }
        length_left--;
        
    }
	return (ret);
}