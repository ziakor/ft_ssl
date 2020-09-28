/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 14:54:36 by dihauet           #+#    #+#             */
/*   Updated: 2020/09/28 17:11:16 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

static void		round_md5(t_md5 *md5)
{
	int			i;
	uint32_t	tmp;

	i = 0;
	// printf("[%d] A=%zu B=%zu C=%zu D=%zu\n", i, md5->word_a, md5->word_b, md5->word_c, md5->word_d);
	while (i < 64)
	{
		if (i >= 0 && i <= 15)
			func_f(md5, i);
		else if (i >= 16 && i <= 31)
			func_g(md5, i);
		else if (i >= 32 && i <= 47)
			func_h(md5, i);
		else if (i >= 48 && i <= 63)
			func_i(md5, i);
		tmp = md5->word_d;
		md5->word_d = md5->word_c;
		md5->word_c = md5->word_b;
		md5->word_b = ft_left_rotate((md5->word_a + md5->f + g_k_md5[i]
					+ md5->endian_w[md5->g]), g_r_md5[i]) + md5->word_b;
		md5->word_a = tmp;
		i++;
	}
}

static int		concat_words_md5(t_md5 *md5, t_hash *hash)
{
	free(md5->padding.data_with_padding);
	if (!(hash->hashed_data = (uint32_t*)malloc(sizeof(uint32_t) * 4)))
		return (FAILED);
	hash->hashed_data[0] = md5->h0;
	hash->hashed_data[1] = md5->h1;
	hash->hashed_data[2] = md5->h2;
	hash->hashed_data[3] = md5->h3;
	hash->nb_words = 4;
	return (SUCCESS);
}

int				md5(t_hash *hash, char *str, size_t length)
{
	t_md5 md5;
	printf("%d\n", length);
	ft_bzero(&md5, sizeof(t_md5));
	add_padding(&md5.padding, str, length, 1);
	md5.h0 = MD5_H0;
	md5.h1 = MD5_H1;
	md5.h2 = MD5_H2;
	md5.h3 = MD5_H3;
	while (md5.offset < md5.padding.new_length)
	{
		md5.endian_w = (uint32_t*)(md5.padding.data_with_padding + md5.offset);
		
		// for (size_t i = 0; i < 16; i++)
		// {
		// 	printf("[%d] %d\n", i, md5.endian_w[i]);
		// }
		
		md5.word_a = md5.h0;
		md5.word_b = md5.h1;
		md5.word_c = md5.h2;
		md5.word_d = md5.h3;
		round_md5(&md5);
		

		
		md5.h0 = md5.h0 + md5.word_a;
		md5.h1 = md5.h1 + md5.word_b;
		md5.h2 = md5.h2 + md5.word_c;
		md5.h3 = md5.h3 + md5.word_d;
		md5.offset += 64;
	}
	if (!(concat_words_md5(&md5, hash)))
		return (FAILED);
	return (SUCCESS);
}
