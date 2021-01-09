#ifndef DES_H
# define DES_H


int			parse_flag_des(t_parsing *list, char **argv, int *i);
int		des_ecb(t_parsing *list, char *str, size_t length);
#endif