/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:08:54 by dihauet           #+#    #+#             */
/*   Updated: 2021/02/01 16:33:09 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

int		get_option_process_one(t_flags *flags, char *str, char *cmd)
{
	if (ft_strcmp(str, "-p") == 0)
			flags->p = 1;
	else if (ft_strcmp(str, "-q") == 0)
			flags->q = 1;
	else if (ft_strcmp(str, "-r") == 0)
			flags->r = 1;
	else if (ft_strcmp(str, "-s") == 0)
			flags->s = 1;
	else
	{
		ft_invalid_option(str, cmd, ft_list_options_1);
		return (FAILED);
	}
	return (SUCCESS);
}


int     get_password(t_parsing *list, char *prompt)
{
    char *password;
    if (!(password = getpass(prompt)))
        return (FAILED);
    if (!(password = ft_strdup(password)))
        return (FAILED);
    write(1, "Verifying - ", 12);
    if (!(list->flags.password = getpass(prompt)))
    {
        free(password);
        return (FAILED);
    }
    if (ft_strcmp(password, list->flags.password) != 0)
    {
        write(1, "Verify failure\nbad password read\n", 35);
        free(password);
        return (FAILED);
    }
    free(password);
    return (SUCCESS);
}


void        generate_salt(t_parsing *list)
{
    int i;
    const char tab[]= "0123456789ABCDEF";
    unsigned char data[8];
    int fd;
    int j;

    j = 0;
    i = 0;
    fd = open("/dev/urandom", O_RDONLY);
    read(fd, data, 8);
    while (i < 16)
    {
        list->flags.salt[i] = data[j]  < 16 ? '0' : tab[data[j] / 16];
        list->flags.salt[i + 1] = tab[data[j] % 16];
        i = i + 2;
        j++;
    }
    close(fd);
}

static void    put_key(t_parsing *list, int nb, int *count_key)
{
	if (nb > 15)
		put_key(list ,nb / 16, count_key);
	nb %= 16;
	if (nb < 10)
    {
        if (*count_key < 16)
            list->flags.key[*count_key] = '0' + nb;
    }
	else
    {
        if (*count_key < 16)
            list->flags.key[*count_key] = nb + 'a' - 10;
    }
     *count_key = *count_key + 1;

}

void         pbfdk2(t_parsing *list, char *data, size_t length)
{
    char *tmp;
    size_t len;
    int i;
    const char tab[]= "0123456789ABCDEF";
    int j;
    j = 0;
    i = 0;
    tmp = data;
    len = length;
    while (i < 1)
    {
        if (list->list_data->hash.hashed_data)
            free(list->list_data->hash.hashed_data);
        sha256(list, tmp, len);
        tmp = list->list_data->hash.hashed_data;
        len = list->list_data->hash.nb_bits;
        i++;
    }
    i = 0;
    while (i < list->list_data->hash.nb_bits)
    {
        if (list->list_data->hash.hashed_data[i] < 16)
            list->flags.key[j++] = '0';
        put_key(list, list->list_data->hash.hashed_data[i], &j);
        i++;
    }

}

int         generate_key(t_parsing *list)
{
    char *password_with_salt;
    const char tab[]= "0123456789ABCDEF";
    size_t len;
    int i;
    int j;
    
    j = 0;
    i = 0;
    len = (ft_strlen(list->flags.password) * 2) + 16;
    password_with_salt = NULL;
    if (!(password_with_salt = (char*) malloc(sizeof(char) * len)))
        return (FAILED);
    while (list->flags.password[j])
    {
        password_with_salt[i] = list->flags.password[j] < 16 ? '0' : tab[list->flags.password[j] / 16];
        password_with_salt[i + 1] = tab[list->flags.password[j] % 16];
        i = i + 2;
        j++;
    }
    j = 0;
    while (j < 16)
        password_with_salt[i++] = list->flags.salt[j++];
    i = 0;
    pbfdk2(list, password_with_salt, len);
    free(password_with_salt);
    return (SUCCESS);
}