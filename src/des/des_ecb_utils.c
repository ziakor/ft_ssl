/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 16:01:07 by dihauet           #+#    #+#             */
/*   Updated: 2021/01/22 16:01:14 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

uint64_t make_initial_permutation(uint64_t data)
{
    uint64_t ret;
    int i;

    i = 0;
    ret = 0;
    while (i < 64)
    {
        ret <<=1;
        ret += (data >> (64 - g_des_initial_permutation[i])) & 1;
        i++;
    }
    return(ret);
}

uint64_t    make_expansion_permutation(uint64_t e)
{
    uint64_t ret;
    uint64_t tmp;
    int i;
    
    i = 0;
    ret = 0;
    while (i < 48)
    {
        tmp = (e >> (32 - g_des_expansion[i])) & 1;
        ret <<= 1;
        ret += tmp;
        i++;
    }
    return (ret);
}

uint64_t    make_substitution(uint64_t s)
{
    int i;
    int row;
    int col;
    uint64_t tmp;
    uint64_t ret;

    i = 0;
    ret = 0;
    while (i < 8)
    {
        tmp = (s >> (42 - ( i * 6))) & 0x3f;
        row = ((tmp >> 5) << 1) + (tmp & 1);
        col = (tmp >> 1) & 0xf;
        tmp = g_des_substitution_boxes[i][row][col];
        ret <<= 4;
        ret += tmp;
        i++;
    }
    return (ret);
}

uint64_t    make_permutation(uint64_t p)
{
    int i;
    uint64_t tmp;
    uint64_t ret;

    i = 0;
    ret = 0;
    while (i < 32)
    {
        tmp = (p >> (32 - g_des_permutation[i])) & 1;
        ret <<= 1;
        ret += tmp;
        i++;
    }
    return (ret);
}

uint64_t make_reverse_permutation(uint64_t r)
{
    int i;
    uint64_t tmp;
    uint64_t ret;

    i = 0;
    ret = 0;
    while (i < 64)
    {
        tmp = (r >> (64 - g_des_reverse_permutation[i])) & 1;
        ret <<= 1;
        ret += tmp;
        i++;
    }
    return (ret);
}