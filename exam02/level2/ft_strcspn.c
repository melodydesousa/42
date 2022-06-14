#include <stddef.h>
size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t i;
	size_t j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (reject[j])
		{
			if (s[i] == reject[j])
				return (i);
			j++;
		}
		i++;
	}
	i = 0;
	while (s[i])
		i++;
	return (i);
}
//calcule la longueur du segment initial de s 
//qui ne contient que des caractères absents de reject.  
#include <string.h>
#include <stdio.h>
int	main(void)
{
	char s[] = "Hello World";
	char reject[] = "World";

	printf("%ld\n", ft_strcspn(s, reject));
	printf("%ld\n", strcspn(s, reject));
	return (0);
}