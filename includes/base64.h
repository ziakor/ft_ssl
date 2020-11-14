#ifndef BASE64_H
# define BASE64_H

static const char g_base64_char[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

typedef struct s_base64
{
  int pad_count;
  uint32_t n;
  uint8_t n0;
  uint8_t n1;
  uint8_t n2;
  uint8_t n3;
}           t_base64;

int			parse_flag_base64(t_parsing *list, char **argv, int *i);
int base64(t_hash *hash, char *data, size_t length, int encryption_mode);

#endif