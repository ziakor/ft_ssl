/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 16:58:13 by dihauet           #+#    #+#             */
/*   Updated: 2020/09/13 16:59:08 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void	put_hexa(int nb)
{
	if (nb > 15)
		put_hexa(nb / 16);
	nb %= 16;
	if (nb < 10)
		ft_putnbr(nb);
	else
		ft_putchar(nb + 'a' - 10);
}

void		ft_puthexa(int nb)
{
	if (nb < 16)
		ft_putchar('0');
	put_hexa(nb);
}
