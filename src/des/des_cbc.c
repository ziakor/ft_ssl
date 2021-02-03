/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_cbc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 15:01:05 by dihauet           #+#    #+#             */
/*   Updated: 2021/02/03 15:15:27 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

int     des_cbc(t_parsing *list, unsigned char *str, size_t length)
{
    t_des des;
    create_key_des_ecb(list, &des);

    if (list->flags.e)
    {
        
    }
}