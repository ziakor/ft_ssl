/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 11:32:52 by dihauet           #+#    #+#             */
/*   Updated: 2020/10/05 20:57:39 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

void    print_bits1(unsigned char octet)
{
    int z = 128, oct = octet;

    while (z > 0)
    {
        if (oct & z)
            write(1, "1", 1);
        else
            write(1, "0", 1);
        z >>= 1;
    }
}

void sha3_keccakf(uint64_t st[25])
{
    int r;
    uint64_t t;
    uint64_t bc[5];

    r = 0;
    while (r < 24)
    {
    keccak_theta(st, bc, t);
    keccak_rho_pi(st, bc, t);
    keccak_chi(st, bc, t);
    keccak_iota(st, bc, r);
    r++;
    }
}



int sha3_init(t_sha_3 *sha3, int output_length)
{
    ft_bzero(sha3, sizeof(sha3));
    sha3->output_size = output_length / 8;
    sha3->block_size = 200 - 2 * sha3->output_size;
    sha3->rate_size = sha3->block_size * 8;

    printf("p : %d\n", sha3->p);
    return (SUCCESS);
}

int sha3_update(t_sha_3 *sha3, char *data, size_t length)
{
    int j;
    size_t i;

    j = sha3->p;
    i = 0;
    while (i < length)
    {
        sha3->u_state.b[j++] ^= data[i];
        if (j >= sha3->block_size)
        {
            //use keccakf
            // keccakf(sha3->u_state.st);
            sha3_keccakf(sha3->u_state.st);
            j = 0;
        }
        i++;
    }
    sha3->p = j;

    return (SUCCESS);

}

int sha3_final(t_sha_3 *sha3, t_hash *hash)
{
    int i;

    i = 0;
    sha3->u_state.b[sha3->p] ^= 0x06;
    sha3->u_state.b[sha3->block_size - 1] ^= 0x80;
    //use keccakf;
    // keccakf(sha3->u_state.st);
    sha3_keccakf(sha3->u_state.st);

    // if (!(hash->hashed_data = (uint8_t*)malloc(sizeof(sha3->output_size))))
    //     return (FAILED);
    while (i < sha3->output_size)
    {
        //ecrire la sortie
        ft_puthexa(sha3->u_state.b[i]);
        // hash->hashed_data[i] = sha3->u_state.b[i];
        i++;
    }
    // for (size_t k = 0; k < 200; k++)
    // {
    //     print_bits1(sha3->u_state.b[k]);
    //     ft_putchar(' ');
    //     /* code */
    // }
    ft_putchar('\n');
}