/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:50:18 by dihauet           #+#    #+#             */
/*   Updated: 2021/01/17 19:06:24 by dihauet          ###   ########.fr       */
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

void rotate_array(int c[17][28], int d[17][28])
{
    int i;
    int j;
    int first_c;
    int first_d;
    
    j = 0;
    i = 1;
    while (i <= 17)
    {   
        first_c = c[i - 1][0];
        first_d = d[i - 1][0];

        j = 0;
        while (j < 27)
        {
            c[i][j] = c[i - 1][j + 1];
            d[i][j] = d[i - 1][j + 1];
            j++; 
        }
        c[i][j] = first_c;
        d[i][j] = first_d;
        if (i != 1 && i != 2 && i != 9 && i != 16)
        {
            j = 0;
            first_c = c[i][0];
            first_d = d[i][0];
            while (j < 27)
            {
                c[i][j] = c[i][j + 1];
                d[i][j] = d[i][j + 1];
                j++; 
            }
            c[i][j] = first_c;
            d[i][j] = first_d;
        }
        i++;
    }
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
			d[0][i - 28] = des->key56bit[i];
    }
    for (size_t i = 0; i < 28; i++)
    {
        printf("%d", c[0][i]);
    }
    printf("\n");
    for (size_t i = 0; i < 28; i++)
    {
        printf("%d", d[0][i]);
    }
    printf("\n-----\n");
    
    int j = 0;
    
    rotate_array(c, d);

    for (int j = 0; j < 17; j++) 
	{
		for (int i = 0; i < 28; i++)
			cd[j][i] = c[j][i];
		for (int i = 28; i < 56; i++)
			cd[j][i] = d[j][i - 28];
	}
    for (size_t j = 0; j < 16; j++)
    {
        for (size_t i = 0; i < 56; i++)
        {
            printf("%d", cd[j][i]);
        }
        printf("\n");
    }


////////////////////
    for (int j = 0; j < 16; j++)
        for (int i = 0; i < 56; i++)
            key56to48(j, i, cd[j + 1][i], des);
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
