/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 12:38:56 by dihauet           #+#    #+#             */
/*   Updated: 2021/09/18 10:07:37 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
#include <unistd.h>
# include <string.h>
# include <errno.h>
# include <stddef.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include "../Libft/includes/libft.h"
# include <limits.h>
# include "structure.h"
# include "./parsing.h"
# include "./base64.h"
# include "./sha256.h"
# include "./md5.h"
# include "./sha3.h"
# include "./des.h"

# define SUCCESS 1
# define FAILED 0

void	print_one(t_list_data *list, t_flags flag, char *cmd);
void    print_two(t_list_data *list, t_flags flag, char *cmd);
void    print_des(t_list_data *list, t_flags flag, char *cmd);
int         process_des(char **argv, t_parsing *list, int i);
static const t_parsing	g_all_cmd[] =
{
	{"md5", 0, 0, {0}, NULL, md5, process_one, print_one},
	{"sha256", 0, 0, {0}, NULL, sha256, process_one, print_one},
	{"sha3-224", 0, 0, {0}, NULL, sha3_224, process_one, print_one},
	{"sha3-256", 0, 0, {0}, NULL, sha3_256, process_one, print_one},
	{"sha3-384", 0, 0, {0}, NULL, sha3_384, process_one, print_one},
	{"sha3-512", 0, 0, {0}, NULL, sha3_512, process_one, print_one},
	{"base64", 0, 1, {0}, NULL, base64, process_two, print_two},
  {"des", 0 , 1 , {0}, NULL, des_ecb, process_des, print_des},
  {"des-ecb", 0 , 1 , {0}, NULL, des_ecb, process_des, print_des},
  {"des-cbc", 0 , 1 , {0}, NULL, des_cbc, process_des, print_des},
	{NULL, 0, 1, {0}, NULL, NULL, NULL, NULL},
};

/*
**flag_utils.c
*/
int		get_option_process_one(t_flags *flags, char *str, char *cmd);

int     get_password(t_parsing *list, char *prompt);
void        generate_salt(t_parsing *list);
void         pbfdk2(t_parsing *list, char *data, size_t length);
int         generate_key(t_parsing *list);
/*
** usage.c
** functions about usage error message
*/
void ft_ssl_help(void);
void		ft_ssl_usage();
void		ft_list_commands();
void		ft_list_message_digest();
void		ft_list_cipher();
void	  ft_list_options_1(void);
void    ft_list_options_base64(void);
void		ft_invalid_command(char *command);
int		ft_invalid_option(char *option, char *command, void list_options(void));
void    ft_list_options_des(void);

/*
** error.c
** functions about error message (open, read,...)
*/

void		error_open_directory(char *file_name, char *cmd);
void		error_open_file(char *file_name, char *cmd);

/*
** clean.c
** function free malloc
*/

void		clean_parsing(t_parsing *list);

/*
** hash.c
** function about hash(md5,sha256,etc..)
*/

int			hash_data(t_parsing *list);

/*
** print.c
** function to print hashed data
*/

void		print_list_hash(t_list_data *list, t_flags flags);

/*
** print_utils.c
** functions used in print.c
*/

void		print_algo_name(char *cmd, int fd);
void		print_hash_data(uint8_t *hash, size_t nb_bits);
void		print_hash(t_hash hash, char *file_name, int write_hexa);
void		print_reverse_hash(t_hash hash, char *file_name);

int	print_flag_p(uint8_t *data, size_t length, int flag_p);
int print_flag_q(uint8_t *data, size_t length, int flag_q);
int print_flag_r(uint8_t *data, size_t length, char *filename, int flag_r);
int print_error(uint8_t *data, size_t length, char *filename, int fd);
/*
** padding.c
** function about padding
*/

int			add_padding(t_padding *padding, unsigned  char *data,
				size_t length, size_t endian);

/*
** utils.c
*/
int			is_little_endian(void);
uint32_t	swap_endian(uint32_t x);
uint64_t    hex_to_uint64(unsigned char *str);
int ahex2int(char a, char b);
void          generate_vector(t_parsing *list);



#endif
