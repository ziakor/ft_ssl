/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_next_prime.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 11:31:05 by dihauet           #+#    #+#             */
/*   Updated: 2020/08/24 11:31:06 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int		ft_is_prime(int nb)
{
	int i;

	i = 2;
	while (nb % i != 0)
	{
		if (i > nb)
			break ;
		i++;
	}
	if (nb == i)
		return (1);
	return (0);
}

int				ft_find_next_prime(int nb)
{
	while (1)
	{
		if (ft_is_prime(nb))
		{
			return (nb);
		}
		nb++;
	}
}
