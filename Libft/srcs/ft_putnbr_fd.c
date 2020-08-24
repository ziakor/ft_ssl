/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 11:57:54 by dihauet           #+#    #+#             */
/*   Updated: 2020/08/24 11:57:54 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int size;
	int nbr;

	size = 1;
	if ((n < 0) && (n != -2147483648))
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n == -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd('2', fd);
		n = 147483648;
	}
	nbr = n;
	while ((nbr /= 10) > 0)
		size *= 10;
	nbr = n;
	while (size >= 1)
	{
		ft_putchar_fd((char)((nbr / size) + 48), fd);
		nbr %= size;
		size /= 10;
	}
}
