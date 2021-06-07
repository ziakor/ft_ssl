/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 10:10:16 by dihauet           #+#    #+#             */
/*   Updated: 2021/06/07 12:40:25 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

uint64_t shift_left_half_keys(uint64_t key, int bits )
{
    uint64_t ret;
    uint64_t tmp;
    uint64_t mutate;

    tmp = bits;
    mutate = 0;
    while (tmp--)
        mutate = (mutate << 1) + 1;
    tmp = (key >> (bits - 1)) & 1;
    ret = ((key << 1) + tmp) & mutate;
    return(ret);
}

void make_half_keys(uint64_t half_keys[16], uint64_t starter)
{
    int i;
    unsigned char shift;
    uint64_t new_half;

    i = 0;
    while (i < 16)
    {
        shift = g_des_shift[i];
        while (shift--)
        {
            new_half = shift_left_half_keys(starter, 28);
            starter = new_half;
        }
        half_keys[i] = new_half;
        i++;
    }
}

uint64_t    make_cp1(uint64_t key64)
{
    int i;
    uint64_t ret;

    ret = 0;
    i = 0;
    while (i < 56)
    {
        ret <<=1;
        ret |= (key64 >> (64 - g_des_cp1[i])) & 1;
        i++;
    }
    ret <<= 8;
    return(ret);
}

uint64_t make_cp2(uint64_t c, uint64_t d)
{
    int i;
    uint64_t key48;
    uint64_t cd;

    cd = (c << 28) | d;
    i = 0;
    key48 = 0;
    while (i < 48)
    {
        key48 <<= 1;
        key48 += ((cd >> (56 - g_des_cp2[i])) & 1);
        i++;
    }
    return(key48);

    
}
void create_key_des_ecb(t_parsing *list, t_des *des)
{
    uint64_t key64;
    uint64_t key56;
    uint64_t c[16];
    uint64_t d[16];


    key64 = hex_to_uint64(list->flags.key);
    key56 = make_cp1(key64);
    make_half_keys(c, (key56 >> 36) & 0xfffffff);
    make_half_keys(d, (key56 >> 8) & 0xfffffff);

    for (size_t n = 0; n < 16; n++)
    {
        key64 = n;
        if (!list->flags.e)
            key64 = 15 - n;
        des->key48[key64] = make_cp2(c[n], d[n]);
    }
}