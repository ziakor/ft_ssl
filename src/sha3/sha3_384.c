/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha3_384.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 20:40:32 by dihauet           #+#    #+#             */
/*   Updated: 2021/06/07 12:22:58 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

int		sha3_384(t_parsing *list, unsigned char *str, size_t length)
{
	t_sha_3		sha3;

	ft_bzero(&sha3, sizeof(t_sha_3));
	sha3_init(&sha3, 384);
	sha3_update(&sha3, (char*)str, length);
	if (!(sha3_final(&sha3, &list->list_data->hash)))
		return (FAILED);
    return (SUCCESS);
}
