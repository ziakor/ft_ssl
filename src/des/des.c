/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:50:18 by dihauet           #+#    #+#             */
/*   Updated: 2021/01/15 17:29:37 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"


void printBits(unsigned int num)
{
   const int bit_cnt = sizeof(unsigned int) * 8;
   unsigned int mask = (1 << (bit_cnt - 1));

   do
   {
      printf("%u", (num & mask) != 0?1:0);
      mask >>= 1;
   } while (mask > 0);
}

int rotateLeft(int x, int n) {
	return (x << n) | (x >> (32 - n)) & ~(-1 << n);
}

int key64to56(int pos, int bit, t_des *des)
{
    int i = 0;

    i = 0;
    while (i < 56)
    {
        if (g_des_cp1[i] == pos + 1)
            break;
        i++;
    }
    des->key56bit[i] = bit;
}

void key56to48(int round, int pos, int text, t_des *des)
{
	int i;
	for (i = 0; i < 56; i++)
		if (g_des_cp2[i] == pos + 1)
			break;
	des->key48bit[round][i] = text;
}

void    key64to48(t_des *des, unsigned int key[64])
{
    int k;
    int backup[17][2];
	int cd[17][56];
	int c[17][28];
	int d[17][28];
	int i;

    i = 0;
    for (size_t i = 0; i < 64; i++)
    {
        key64to56(i,key[i], des);
    }

    for (size_t i = 0; i < 56; i++)
    {
		if (i < 28)
			c[0][i] = des->key56bit[i];
		else
			d[0][i] = des->key56bit[i];
    }
    int j = 0;
    for (size_t x = 0; x < 17; x++)
    {
		int shift = g_des_shift[x - 1];

		for (int i = 0; i < shift; i++)
			backup[x - 1][i] = c[x - 1][i];
		for (int i = 0; i < (28 - shift); i++)
			c[x][i] = c[x - 1][i + shift];
		k = 0;
		for (int i = 28 - shift; i < 28; i++)
			c[x][i] = backup[x - 1][k++];

		for (int i = 0; i < shift; i++)
			backup[x - 1][i] = d[x - 1][i];
		for (int i = 0; i < (28 - shift); i++)
			d[x][i] = d[x - 1][i + shift];
		k = 0;
		for (int i = 28 - shift; i < 28; i++)
			d[x][i] = backup[x - 1][k++];
    }
    for (int j = 0; j < 17; j++) 
	{
		for (int i = 0; i < 28; i++)
			cd[j][i] = c[j][i];
		for (int i = 28; i < 56; i++)
			cd[j][i] = d[j][i - 28];
	}

	for (int j = 1; j < 17; j++)
		for (int i = 0; i < 56; i++)
			key56to48(j, i, cd[j][i], des);
	
}

int get_hexa(int c)
{
    const char tabhexa[] = "0123456789ABCDEF";
    for (size_t i = 0; i < 16; i++)
    {
        if (c == tabhexa[i])
            return i;
    }
    return(-1);
    
}

void create_key_des(t_parsing *list, t_des *des)
{
    unsigned int key[64];
    int i;
    int j;
    int k;
    int b;
    uint8_t c;

    i = 0;
    j = 0;
    b = 0;
    while (i < 8)
    {
        c = get_hexa(list->flags.key[b]) << 4 | get_hexa(list->flags.key[b + 1]);
        k = 7;
        while (k > -1)
        {
            key[j] = (c >> k) & 1;
            k--;
            j++;
        }
        b += 2;
        i++;
    }
    key64to48(des,key);

}

int		des_ecb(t_parsing *list, char *str, size_t length)
{
    t_des des;
    create_key_des(list, &des);
	exit(0);
	return (SUCCESS);
}
