/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha3_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 12:36:59 by dihauet           #+#    #+#             */
/*   Updated: 2020/10/05 20:51:17 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

void keccak_theta(uint64_t st[25], uint64_t bc[5], uint64_t t)
{
    int i;
    int j;

    j = 0;
    i = 0;
    while (i < 5)
    {
        bc[i] = st[i] ^ st[i + 5] ^ st[i + 10] ^ st[i + 15] ^ st[i + 20];
        i++;
    }
    i = 0;
    while (i < 5)
    {
        t = bc[(i + 4) % 5] ^ ft_rotl64(bc[(i + 1) % 5], 1);
        j = 0;
        while (j < 25)
        {
            st[j + i] ^= t;
            j+=5;
        }
        i++;
    }
}

void keccak_rho_pi(uint64_t st[25], uint64_t bc[5], uint64_t t)
{
    int i;
    int j;

    i = 0;
    t = st[1];
    while (i < 24)
    {
        j = g_pils_sha3[i];
        bc[0] = st[j];
        st[j] = ft_rotl64(t, g_rotate_sha3[i]);
        t = bc[0];
        i++;
    }
}

void keccak_chi(uint64_t st[25], uint64_t bc[5], uint64_t t)
{
    int i;
    int j;

    j = 0;
    i = 0;
    while (j < 25)
    {
        i = 0;
        while (i < 5)
        {
            bc[i] = st[j + i];
            i++;
        }
        i = 0;
        while (i < 5)
        {
            st[j + i] ^= (~bc[(i + 1) % 5]) & bc[(i + 2) % 5];
            i++;
        }
        j +=5;
    }
}

void keccak_iota(uint64_t st[25], uint64_t bc[5], int r)
{
    st[0] ^= g_rc_sha3[r];
}