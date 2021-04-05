/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 17:06:58 by dihauet           #+#    #+#             */
/*   Updated: 2021/04/04 22:24:58 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef	struct		s_flags
{
	int		p;
	int		q;
	int		r;
	int		s;
	uint8_t	salt[16];
	uint8_t	key[16];
	uint8_t	vector[16];
	char	*password;
	int		a;
	int		d;
	int 	e;
	int		i;
	int		o;
  int   P;
	char	*o_file;
}					t_flags;

typedef struct		s_data
{
	char		*file_name;
	int			fd;
	unsigned char		*data;
	size_t		data_length;
}					t_data;

typedef struct		s_list_data
{

	t_data					data;
	t_hash					hash;
	struct s_list_data		*next;
}					t_list_data;

typedef struct		s_parsing
{
	char						*cmd;
	int							size;
	int							is_cipher;
	t_flags						flags;
	t_list_data					*list_data;
	int							(*hash_func)(struct s_parsing*, unsigned char*, size_t);
	int							(*process_func)(char**, struct s_parsing*, int);
  void            (*print_func)(t_list_data*, t_flags, char*, int);

}					t_parsing;

int					parsing_args(t_parsing *list, char **argv, int argc);
char				*get_stdin(void);

/*
** file data_list.c
** function about linked list of parsing structure
*/

t_list_data			*create_new_elem(char *str, char *file_name, int fd,
									int size_data);
void				add_new_elem(t_list_data **list, t_list_data *new_elem);
void				read_data_list(t_list_data *list);

/*
** file parsing_functions.c
*/

int					get_option(t_flags *flags, char c);
int					open_file(char *file_name);
int		get_data_s_flag(t_list_data **list_data, char *data);
char				*get_error_message_open_file(int type, int *size);
/*
** flag.c
**
*/

int flag_print(uint8_t key[16], uint8_t vector[16], uint8_t salt[16]);

/*
**parsing_file.c
**parsing data from file
*/

unsigned char		*read_file_data(int fd, int *size);
int 		get_file_data(t_parsing *list, char *filename);
unsigned char		*concat_list_to_str(t_list *list, int size);

/*
**list_read_data.c
**
*/

t_list		*ft_lst_add_data_to_end(t_list *list, char *data, int size);
char	*free_read_data_list(t_list *list);


/*
** flag.c
**
*/

int flag_input(t_parsing *list, char **argv, int *i);
int flag_output(t_parsing *list, char **argv, int *i);
int flag_a(t_parsing *list);
int flag_vector(t_parsing *list, char **argv, int *i);
void init_flag(t_flags *flag);
/*
** process.c
** file about get flag and data
*/

int			process_one(char **argv, t_parsing *list, int i);

int			process_two
(char **argv, t_parsing *list, int i);

#endif

