/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 17:06:58 by dihauet           #+#    #+#             */
/*   Updated: 2020/11/08 02:49:28 by dihauet          ###   ########.fr       */
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
	int		d;
	int 	e;
	int		i;
	int		o;
	char	*o_file;
}					t_flags;

typedef struct		s_data
{
	char		*file_name;
	int			fd;
	char		*data;
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
	int							(*hash_func)(t_hash*, char*, size_t);
	int							(*process_func)(char **argv, struct s_parsing *list, int i);

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
char				*read_stdin(int *count);
int					open_file(char *file_name);
int		get_data_s_flag(t_list_data **list_data, char *data);
char				*get_error_message_open_file(int type, int *size);

/*
** file interactive_mode.c
** functions about the interactive mode
*/

int					interactive_mode(t_parsing *list);
int					free_interactive_mode(char *binary, char *line,
							char **args);
/*
** flag.c
**
*/

/*
**parsing_file.c
**parsing data from file
*/

char		*read_file_data(int fd, int *size);
int 		get_file_data(t_parsing *list, char *filename);
char		*concat_list_to_str(t_list *list, int size);

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
/*
** process.c
** file about get flag and data
*/

int			process_one(char **argv, t_parsing *list, int i);

int			process_base64(char **argv, t_parsing *list, int i);

#endif

