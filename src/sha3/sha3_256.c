/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha3_256.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 11:25:38 by dihauet           #+#    #+#             */
/*   Updated: 2020/10/07 20:32:47 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

int		sha3_256(t_hash *hash, char *str, size_t length)
{
	t_sha_3		sha3;

	ft_bzero(&sha3, sizeof(t_sha_3));
	sha3_init(&sha3, 256);
	sha3_update(&sha3, str, length);
	if (!(sha3_final(&sha3, hash)))
		return (FAILED);
}
