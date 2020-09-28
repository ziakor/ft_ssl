/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 11:31:31 by dihauet           #+#    #+#             */
/*   Updated: 2020/09/18 11:56:20 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

void		init_sha256(t_sha256 *sha256)
{
	ft_bzero(sha256, sizeof(t_sha256));
	sha256->h0 = SHA256_H0;
	sha256->h1 = SHA256_H1;
	sha256->h2 = SHA256_H2;
	sha256->h3 = SHA256_H3;
	sha256->h4 = SHA256_H4;
	sha256->h5 = SHA256_H5;
	sha256->h6 = SHA256_H6;
	sha256->h7 = SHA256_H7;
}

uint32_t	func_s0(int i, t_sha256 *sha256)
{
	return (ft_right_rotate(sha256->words[i - 15], 7) ^
		ft_right_rotate(sha256->words[i - 15], 18)
			^ sha256->words[i - 15] >> 3);
}

uint32_t	func_s1(int i, t_sha256 *sha256)
{
	return (ft_right_rotate(sha256->words[i - 2], 17)
		^ ft_right_rotate(sha256->words[i - 2], 19)
			^ sha256->words[i - 2] >> 10);
}
