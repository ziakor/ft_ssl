/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:52:29 by dihauet           #+#    #+#             */
/*   Updated: 2020/11/14 03:01:05 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

static int  init_base64_encrypt(t_hash *hash, t_base64 *b64, char *data, size_t length)
{
    b64->pad_count = length % 3;

    hash->nb_bits = (length + 2) / 3 * 4;
    if (!(hash->hashed_data = (uint8_t*)malloc(sizeof(uint8_t) * hash->nb_bits)))
        return (FAILED);
    return (SUCCESS);

}

static int base64_decrypt(t_hash *hash, char *data, size_t length)
{

}

void    print_bits(unsigned char octet)
{
    int z = 32, oct = octet;

    while (z > 0)
    {
        if (oct & z)
            write(1, "1", 1);
        else
            write(1, "0", 1);
        z >>= 1;
    }
}

static int base64_encrypt(t_hash *hash, char *data, size_t length)
{
    int i;
    t_base64 b64;
    int res_i;
    
    res_i = 0;
    i = 0;
    if (!(init_base64_encrypt(hash, &b64, data, length)))
        return (FAILED);
    while (i <  length)
    {
        b64.n = ((uint32_t)data[i]) << 16;
        if((i+1) < length)
            b64.n += ((uint32_t)data[i+1]) << 8;
        if((i+2) < length)
            b64.n += data[i+2];
        b64.n0 = (uint8_t)(b64.n >> 18) &  63;
        b64.n1 = (uint8_t)(b64.n >> 12) &  63;
        b64.n2 = (uint8_t)(b64.n >> 6) &  63;
        b64.n3 = ((uint8_t)b64.n) &  63;
        hash->hashed_data[res_i++] = g_base64_char[b64.n0];
        hash->hashed_data[res_i++] = g_base64_char[b64.n1];
        if (i + 1  < length)
            hash->hashed_data[res_i++] = g_base64_char[b64.n2];
        if (i + 2 < length)
            hash->hashed_data[res_i++] = g_base64_char[b64.n3];
        i += 3;
    }
    if (b64.pad_count > 0)
    {
        while (b64.pad_count < 3)
        {
            hash->hashed_data[res_i++] = '=';
            b64.pad_count++;
        }
    }
    return (SUCCESS);
}



int base64(t_hash *hash, char *data, size_t length, int encryption_mode)
{
    printf("asdasd\n");
    if (encryption_mode)
    {
        if (!(base64_encrypt(hash, data, length)))
            return (FAILED);
    }
    else
    {
        if (!(base64_decrypt(hash, data, length)))
            return (FAILED);
    }
    return (SUCCESS);
}