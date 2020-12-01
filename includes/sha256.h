/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 13:16:28 by dihauet           #+#    #+#             */
/*   Updated: 2020/11/14 12:49:05 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_H
# define SHA256_H

# define SHA256_H0 0x6A09E667
# define SHA256_H1 0xBB67AE85
# define SHA256_H2 0x3C6EF372
# define SHA256_H3 0xA54FF53A
# define SHA256_H4 0x510E527F
# define SHA256_H5 0x9B05688C
# define SHA256_H6 0x1F83D9AB
# define SHA256_H7 0x5BE0CD19

static const uint32_t g_k_sha256[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
	0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
	0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
	0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
	0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
	0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

typedef struct		s_sha256
{
	int			h0;
	int			h1;
	int			h2;
	int			h3;
	int			h4;
	int			h5;
	int			h6;
	int			h7;
	size_t		offset;
	uint32_t	ch;
	uint32_t	maj;
	uint32_t	word_a;
	uint32_t	word_b;
	uint32_t	word_c;
	uint32_t	word_d;
	uint32_t	word_e;
	uint32_t	word_f;
	uint32_t	word_g;
	uint32_t	word_h;
	uint32_t	*words;
	t_padding	padding;
}					t_sha256;

/*
** sha256.c
** file about algorithm sha256
*/

int					sha256(t_parsing *list, char *str, size_t length);
void				init_sha256(t_sha256 *sha256);
uint32_t			func_s0(int i, t_sha256 *sha256);
uint32_t			func_s1(int i, t_sha256 *sha256);
#endif
