/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 11:32:52 by dihauet           #+#    #+#             */
/*   Updated: 2020/12/02 17:32:53 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

void		sha3_keccakf(uint64_t st[25])
{
	int			r;
	uint64_t	t;
	uint64_t	bc[5];

	r = 0;
    t = 0;
	while (r < 24)
	{
		keccak_theta(st, bc, t);
		keccak_rho_pi(st, bc, t);
		keccak_chi(st, bc);
		keccak_iota(st, r);
		r++;
	}
}

int			sha3_init(t_sha_3 *sha3, int output_length)
{
	ft_bzero(sha3, sizeof(sha3));
	sha3->output_size = output_length / 8;
	sha3->block_size = 200 - 2 * sha3->output_size;
	sha3->rate_size = sha3->block_size * 8;
	return (SUCCESS);
}

int			sha3_update(t_sha_3 *sha3, char *data, size_t length)
{
	int		j;
	size_t	i;

	j = sha3->p;
	i = 0;
	while (i < length)
	{
		sha3->u_state.b[j++] ^= data[i];
		if (j >= sha3->block_size)
		{
			sha3_keccakf(sha3->u_state.st);
			j = 0;
		}
		i++;
	}
	sha3->p = j;
	return (SUCCESS);
}

int			sha3_final(t_sha_3 *sha3, t_hash *hash)
{
	int i;

	i = 0;
	sha3->u_state.b[sha3->p] ^= 0x06;
	sha3->u_state.b[sha3->block_size - 1] ^= 0x80;
	sha3_keccakf(sha3->u_state.st);
	if (!(hash->hashed_data = (uint8_t*)malloc(sizeof(uint8_t)
	* sha3->output_size)))
		return (FAILED);
	while (i < sha3->output_size)
	{
		hash->hashed_data[i] = sha3->u_state.b[i];
		i++;
	}
	hash->nb_bits = sha3->output_size;
	return (SUCCESS);
}
