// Rajouter le header !

#ifndef PARSING_H
# define PARSING_H

typedef struct	s_flags
{
	int	p;
	int	q;
	int	r;
	int	s;
}				t_flags;

typedef struct	s_data
{
	char	*file_name;
	int		fd;
	char	*data;
	size_t	data_length;
}				t_data;

typedef struct	s_list_data
{

	t_data				data;
	struct s_list_data	*next;
}				t_list_data;



typedef struct	s_parsing
{
	char		*cmd;
	t_flags		flags;
	t_list_data	*list_data;
	int (*hash_func)(char*, size_t);
	void (*print_func)(void*);
}				t_parsing;

int				parsing_args(t_parsing *list, char **argv, int argc);
char			*get_stdin();

/*
** file data_list.c
** function about linked list of parsing structure
*/

t_list_data		*create_new_elem(char *str, char *file_name, int fd);
void			add_new_elem(t_list_data **list, t_list_data *new_elem);
void			read_data_list(t_list_data *list);

/*
** file parsing_functions.c
*/

int				get_option(t_flags *flags, char c);
char			*read_stdin();
int				open_file(char *file_name, char *cmd);
char			*get_error_message_open_file(int type);
char			*read_file(int fd);

/*
** file interactive_mode.c
** functions about the interactive mode
*/

int				interactive_mode(t_parsing *list);
int		free_interactive_mode(char *binary, char *line, char **args);
#endif
