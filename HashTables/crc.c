#include "nmmintrin.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

char 	**g_hashtable;

int		init_hash(uint64_t size)
{
	if (!(g_hashtable = calloc(size, sizeof(char **))))
		return(EXIT_FAILURE);
	return(EXIT_SUCCESS);
}

int		hash_addstring(char *key, char *val)
{
	uint32_t	hash;
	size_t		len;
	int			ret;

	len = 0;
	hash = 0;
	ret = 0;
	while (key[len])
	{
		hash = _mm_crc32_u8(hash, key[len]);
		len++;
	}
	if (g_hashtable[hash])
	{
		free(g_hashtable[hash]);
		ret = 1;
	}
	len = strlen(val);
	if (!(g_hashtable[hash] = calloc(len + 1, sizeof(char))))
		return (-1);
	memcpy(g_hashtable[hash], val, len);
	return (ret);
}

char	*hash_fetchval(char *key)
{
	uint32_t	hash;
	size_t		len;

	hash = 0;
	len = 0;
	while (key[len])
	{
		hash = _mm_crc32_u8(hash, key[len]);
		len++;
	}
	return (g_hashtable[hash]);
}

int		main(int argc, char *argv[])
{
	uint64_t	hash;
	int			i;
	int			ret;

	if (init_hash(1L << 32))
	{
		printf("Failed to init(%s)\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	i = 1;
	while (i < argc && (i + 1) < argc)
	{
		if ((ret = hash_addstring(argv[i], argv[i + 1])) == -1)
			printf("Failed to add string! %s\n", strerror(errno));
		if (ret == 1)
			printf("Collision :(\n");
		i += 2;
	}
	i = 1;
	while (i < argc && (i + 1) < argc)
	{
		printf("Key: %s Val: %s\n", argv[i], hash_fetchval(argv[i]));
		i += 2;
	}
}
