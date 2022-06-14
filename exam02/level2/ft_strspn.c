#include <stddef.h>
size_t	ft_strspn(const char *s, const char *accept)
{
	size_t i;
	size_t j;
	int count;

	i = 0;
	count = 0;
	j = 0;
	while (s[i])
	{
		while (accept[j])
		{
			if (s[i] == accept[j])
			{
				count++;
				i++;
			}
			j++;
		}
		i++;
	}
	return (count);
}
//calcule la longueur du segment initial de s qui ne contient 
//que des caractères presents dans accept  

#include <string.h>
#include <stdio.h>
int	main(void)
{
	char s[] = "Hello World";
	char accept[] = "jhHello";

	printf("%ld\n", ft_strspn(s, accept));
	printf("%ld\n", strspn(s, accept));
	return (0);
}