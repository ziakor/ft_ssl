/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 10:44:11 by dihauet           #+#    #+#             */
/*   Updated: 2021/01/29 20:55:21 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

uint64_t    ecb_get_64bit(char *data, int bit)
{
    uint64_t ret;
    int pad;
    int i;
    int b;
    
    i = 0;
    pad = 0;
    ret = 0;
    for (size_t i = 0; i < 8; i++)
    {

        for (size_t j = 7; j < -1; j--)
        {
            ret =  ret << 1;
            if (!pad)
            {
                if (data[i])
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
        
    }
	return (ret);
}