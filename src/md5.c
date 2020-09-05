/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 14:54:36 by dihauet           #+#    #+#             */
/*   Updated: 2020/09/05 20:35:59 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

int     add_padding(t_md5 *md5, char* data, size_t length)
{
    md5->padding.initial_length = length;
    md5->padding.nb_bits = length * 8;
    md5->padding.new_length = (((448 - (md5->padding.nb_bits + 1)) % 512) + 64
    + 1) / 8;
    if (!(md5->padding.data_with_padding = (uint8_t*)malloc(sizeof(uint8_t)
    * md5->padding.new_length)))
        return(0);
    ft_memcpy(md5->padding.data_with_padding, data, length);
    md5->padding.data_with_padding[length] |= 1 <<7;
    ft_memcpy(md5->padding.data_with_padding + md5->padding.new_length - 8,
    &(md5->padding.nb_bits), 8);
    return(1);
}

int     md5(char *str, size_t length)
{
    t_md5 md5;

    ft_bzero(&md5, sizeof(t_md5));
    printf("MD5\n");
    return (1);
}

// (448 - (p->nb_bits + 1)) % 512


