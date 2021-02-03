#ifndef BASE64_H
# define BASE64_H
# define WHITESPACE 64
# define EQUALS     65
# define INVALID    66

static const unsigned char g_base64_char[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static const unsigned char g_base64_d[]= {
    66,66,66,66,66,66,66,66,66,66,64,66,66,66,66,66,66,66,66,66,66,66,66,66,66,
    66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,62,66,66,66,63,52,53,
    54,55,56,57,58,59,60,61,66,66,66,65,66,66,66, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,66,66,66,66,66,66,26,27,28,
    29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,66,66,
    66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,
    66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,
    66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,
    66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,
    66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,
    66,66,66,66,66,66
};

typedef struct s_base64
{
  int pad_count;
  int decode_length;
  uint32_t n;
  uint8_t n0;
  uint8_t n1;
  uint8_t n2;
  uint8_t n3;
  uint32_t buffer;
  size_t i;
  int j;
  unsigned char c;
  char iter;
}           t_base64;

int			parse_flag_base64(t_parsing *list, char **argv, int *i);
int     base64_encrypt(t_parsing *list, unsigned char *data, size_t length);
int     base64_decrypt(t_parsing *list, unsigned char *data, size_t length);
int base64(t_parsing *list, unsigned char *data, size_t length);
#endif