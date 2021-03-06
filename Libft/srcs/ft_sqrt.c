/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 11:39:23 by dihauet           #+#    #+#             */
/*   Updated: 2020/08/24 11:39:25 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_sqrt(int nb)
{
	int i;

	i = 1;
	if (nb == 1)
		return (1);
	while (i < nb)
	{
		if (((nb / i) == i) && (nb % i == 0))
			return (i);
		else
			i++;
	}
	return (0);
}
