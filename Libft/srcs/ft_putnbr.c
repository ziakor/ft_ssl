/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 11:37:49 by dihauet           #+#    #+#             */
/*   Updated: 2020/08/24 11:37:50 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_putnbr(int n)
{
	int size;
	int nbr;

	size = 1;
	if ((n < 0) && (n != -2147483648))
	{
		ft_putchar('-');
		n = -n;
	}
	if (n == -2147483648)
	{
		ft_putchar('-');
		ft_putchar('2');
		n = 147483648;
	}
	nbr = n;
	while ((nbr /= 10) > 0)
		size *= 10;
	nbr = n;
	while (size >= 1)
	{
		ft_putchar((char)((nbr / size) + 48));
		nbr %= size;
		size /= 10;
	}
}
