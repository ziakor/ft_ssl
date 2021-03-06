/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_if.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 11:30:52 by dihauet           #+#    #+#             */
/*   Updated: 2020/08/24 11:30:54 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_count_if(char **tab, int (*f)(char *))
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (tab[i])
	{
		if (f(tab[i]) == 1)
			k++;
		i++;
	}
	return (k);
}
