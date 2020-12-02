/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 11:00:51 by dihauet           #+#    #+#             */
/*   Updated: 2020/12/02 16:59:04 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA3_H
# define SHA3_H

# define SHA3_224_HASH_SIZE 28
# define SHA3_256_HASH_SIZE 32
# define SHA3_384_HASH_SIZE 48
# define SHA3_512_HASH_SIZE 64
# define KECCAKF_ROUNDS 24

static const uint64_t g_rc_sha3[24] = {
	0x0000000000000001, 0x0000000000008082, 0x800000000000808a,
	0x8000000080008000, 0x000000000000808b, 0x0000000080000001,
	0x8000000080008081, 0x8000000000008009, 0x000000000000008a,
	0x0000000000000088, 0x0000000080008009, 0x000000008000000a,
	0x000000008000808b, 0x800000000000008b, 0x8000000000008089,
	0x8000000000008003, 0x8000000000008002, 0x8000000000000080,
	0x000000000000800a, 0x800000008000000a, 0x8000000080008081,
	0x8000000000008080, 0x0000000080000001, 0x8000000080008008
};

static const int g_rotate_sha3[24] = {
	1, 3, 6, 10, 15, 21, 28, 36, 45, 55, 2, 14,
	27, 41, 56, 8, 25, 43, 62, 18, 39, 61, 20, 44
};

static const int g_pils_sha3[24] = {
	10, 7, 11, 17, 18, 3, 5, 16, 8, 21, 24, 4,
	15, 23, 19, 13, 12, 2, 20, 14, 22, 9, 6, 1
};

typedef struct			s_sha_3
{
	int					rate_size;
	int					block_size;
	int					output_size;
	int					p;
	union
	{
		uint8_t			b[200];
		uint64_t		st[25];
	}					u_state;
	t_padding			padding;
}						t_sha_3;

/*
** sha3.c
*/
int						sha3_init(t_sha_3 *sha3, int output_length);
int						sha3_update(t_sha_3 *sha3, char *data, size_t length);
int						sha3_final(t_sha_3 *sha3, t_hash *hash);
int						sha3_224(t_parsing *list, char *str, size_t length);
int						sha3_256(t_parsing *list, char *str, size_t length);
int						sha3_384(t_parsing *list, char *str, size_t length);
int						sha3_512(t_parsing *list, char *str, size_t length);

/*
** sha3_utils.c
*/
void					keccak_theta(uint64_t st[25], uint64_t bc[5],
								uint64_t t);
void					keccak_rho_pi(uint64_t st[25], uint64_t bc[5],
								uint64_t t);
void					keccak_chi(uint64_t st[25], uint64_t bc[5]);
void					keccak_iota(uint64_t st[25], int r);

#endif
