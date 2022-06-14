#include <stdlib.h>

char *ft_strdup(char *src)
{
	int i;
	char *dup;

	i = 0;
	while (src[i])
		i++;
	dup = malloc(i + 1);
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (src)
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}