/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:50:18 by dihauet           #+#    #+#             */
/*   Updated: 2021/01/14 13:21:52 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

int key64to56(int pos, int text, t_des *des)
{
	int i;

	i = 0;
	while (i < 56)
	{
		if (g_des_cp1[i]  == pos + 1)
			break;
		des->key56bit[i]= text;
		i++;
	}
}

void    key64to48(t_des *des, t_parsing *list)
{
	int k;
	int backup[17][2];
	int cd[17][56];
	int c[17][28];
	int d[17][28];
	int i;

	i = 0;

	while (i < 64)
	{
		key64to56(i,list->flags.key[i], des);
		i++;
	}
	i = 0;
	while (i < 56)
	{
		if (i < 28)
			c[0][i] = des->key56bit[i];
		else
			d[0][i] = des->key56bit[i];
		i++;
	}

	
}

int		des_ecb(t_parsing *list, char *str, size_t length)
{
	ft_putstr(list->cmd);
	ft_putnstr(str, length);
	ft_putnbr(length);
	exit(0);
	return (SUCCESS);
}