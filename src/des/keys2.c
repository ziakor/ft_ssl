/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 10:44:11 by dihauet           #+#    #+#             */
/*   Updated: 2021/09/15 20:08:56 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

uint64_t    ecb_get_64bit(char *data, int bit, int length_left)
{
		uint64_t ret;
		int pad;
		
		pad = 0;
		ret = 0;
		for (int i = 0; i < 8; i++)
		{
			for (int  j = 7; j >= 0; j--)
			{
					if (!pad)
					{
							if (length_left > 0)
									ret = (ret << 1) | ((data[i] >> j) & 1);
							else
							{

									ret =  (ret << 8) | ((bit ));
									pad = 1;
                  break;
							}
					}
					else
					{
							ret =   (ret << 8) | ((bit ));
              break;
					}
			}
			length_left--;
			
		}

	return (ret);
}