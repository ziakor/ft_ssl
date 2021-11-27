# FT_SSL

A miniature implementation of openssl implementing several features, namely :
- ft_ssl_md5 subject is [here](./subject_md5.pdf)
- ft_ssl_des subject is [here](./subject_des.pdf)

#### Mandatory part
* md5
* sha256
* base64
* des-ecb
* des-cbc
  
#### Bonus 
* sha3-256
* sha3-224
* sha3-384
* sha3-512

## Usage
```
> ./ft_ssl
usage: ft_ssl command [flags] [file/string]

> ./ft_ssl foobar
ft_ssl: Error: 'foobar' is an invalid command.

> echo "42 is nice" | ./ft_ssl md5
(stdin)= 35f1d6de0302e2086a4e472266efb3a9

>echo "42 is nice" | ./ft_ssl sha3-256
(stdin)= eaa5a1d9440c84c3549c223a398d037c1be9dd2e40e76e0e27ee9191e2b409d2
```

