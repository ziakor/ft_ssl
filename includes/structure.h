/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 17:05:25 by dihauet           #+#    #+#             */
/*   Updated: 2020/10/06 12:25:52 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

# include <stdio.h>
# include <stdint.h>

typedef struct		s_padding
{
	size_t			initial_length;
	size_t			new_length;
	size_t			nb_bits;
	uint8_t			*data_with_padding;
}					t_padding;

typedef struct		s_hash
{
	uint8_t		*hashed_data;
	size_t		nb_bits;
}					t_hash;
#endif
