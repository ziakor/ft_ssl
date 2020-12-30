/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 17:20:04 by dihauet           #+#    #+#             */
/*   Updated: 2020/12/11 19:00:59 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void    ft_putnstr(char *data, size_t length)
{
    size_t i;

    i = 0;

    if (data)
    {
        while (i < length)
        {
            ft_putchar(data[i]);
            i++;
        }
    }
}