/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 15:26:42 by dihauet           #+#    #+#             */
/*   Updated: 2021/06/07 12:12:42 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

uint32_t	swap_endian(uint32_t x)
{
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;

	a = x >> 24 & 0xff;
	b = x >> 8 & 0xff00;
	c = x << 8 & 0xff0000;
	d = x << 24 & 0xff000000;
	return (a | b | c | d);
}

uint64_t    hex_to_uint64(unsigned char *str)
{
    int i;
    uint64_t key;

    i = 0;
    key = 0;
    while (i < 16)
    {
        key <<= 4;
        if (str[i] >= '0' && str[i] <= '9')
            key |= (str[i] - '0');
        if (str[i] >= 'A' && str[i] <= 'F')
            key |= ((str[i] - 'A') + 10);
        i++;
    }
    return (key);
}