/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:50:18 by dihauet           #+#    #+#             */
/*   Updated: 2021/01/21 18:32:56 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"
#include <inttypes.h>

int rotateLeft(int x, int n) {
	return (x << n) | (x >> (32 - n)) & ~(-1 << n);
}

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
    uint64_t tmp;

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
        }
        else
        {
            pad = 1;
            ret |= bit;
        }
        i++;
    }
    return (ret);
}

int     des_ecb_encode(t_parsing *list, t_des *des, char *str, size_t length)
{
    size_t i;
    uint64_t data;
    int bit;

    i = 0;
    bit = (((length / 8) + 1 ) * 8) * length; 
    while (i < length || i % 8 != 0)
    {
        printf("%d| mod: %d | boucle\n", i, i % 8);
        data = ecb_get_64bit(str, bit);
        i++;
    }
}

int		des_ecb(t_parsing *list, char *str, size_t length)
{
    t_des des;
    create_key_des_ecb(list, &des);
    printf("%d", length);
    printf("\n%d\n", list->flags.e);
    if(list->flags.e)
    {
        if (!(des_ecb_encode(list, &des, str, length)))
            return (FAILED);
    }
    // uint64_t t = hex_to_uint64(list->flags.key);
    
	exit(0);
	return (SUCCESS);
}
