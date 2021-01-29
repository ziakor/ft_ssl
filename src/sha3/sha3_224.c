/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha3_224.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 20:40:46 by dihauet           #+#    #+#             */
/*   Updated: 2021/01/29 11:49:41 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

int		sha3_224(t_parsing *list, unsigned char *str, size_t length)
{
	t_sha_3		sha3;

	ft_bzero(&sha3, sizeof(t_sha_3));
	sha3_init(&sha3, 224);
	sha3_update(&sha3, str, length);
	if (!(sha3_final(&sha3, &list->list_data->hash)))
		return (FAILED);
    return (SUCCESS);
}
