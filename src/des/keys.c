/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 10:10:16 by dihauet           #+#    #+#             */
/*   Updated: 2021/09/14 15:43:48 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

uint64_t shift_left_half_keys(uint64_t key, int bits )
{
	uint64_t	left;
	uint64_t	right;

	left = (key >> 36) << 36;
	right = key << 28;
	left = (((left | (left >> 28)) << bits) >> 36) << 36;
	right = (((right | (right >> 28)) << bits) >> 36) << 36;
	return (left | (right >> 28));
}

void make_half_keys(uint64_t c[16], u_int64_t d[16], uint64_t key56)
{
  int i = 0;
  uint64_t newKey = 0;
  
  newKey = key56;
 
  while (i < 16) {
    newKey = shift_left_half_keys(newKey, g_des_shift[i]);
    c[i] = newKey >> 36;
    d[i] = (newKey << 28) >> 36; 
    i++;
  }
}

uint64_t    make_pc1(uint64_t key64)
{
  uint64_t	new_block;
	uint64_t	new_val;
	int			i;

	new_block = 0;
	i = -1;
	while (++i < 56)
	{
		new_val = ((key64 >> (64 - g_des_pc1[i])) & 1);
		if (new_val)
			new_block |= (new_val << (64 - (i + 1)));
	}
    return(new_block);
}

uint64_t make_cp2(uint64_t c, uint64_t d)
{
    int i;
    uint64_t key48;
    uint64_t cd;

    cd = (c << 28) | d;
    i = 0;
    key48 = 0;
    while (i < 48)
    {
        key48 <<= 1;
        key48 += ((cd >> (56 - g_des_cp2[i])) & 1);
        i++;
    }
    return(key48);
}


void create_key_des_ecb(t_parsing *list, t_des *des)
{
    uint64_t key64;
    uint64_t key56;
    uint64_t c[16]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    uint64_t d[16]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    int k = 63;

    key64 = hex_to_uint64(list->flags.key);
    printf("key64: ");
        while (k >= 0){
      printf("%d", (key64 >> k) & 1);
      k--;
    }
    
    key56 = make_pc1(key64);
    k = 63;
    printf("\nkey56: ");
      while (k >= 8){
        printf("%d", (key56 >> k) & 1);
      k--;
    }



  
    make_half_keys(c, d, key56);
  printf("\n");
    for (size_t n = 0; n < 16; n++)
    {
        key64 = n;
        if (!list->flags.e)
            key64 = 15 - n;
        des->key48[key64] = make_cp2(c[n], d[n]);
    }
}