#include <stddef.h>
#include <stdio.h>
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
		j = 0;
		while (accept[j])
		{
			if (s[i] == accept[j])
			{
				count++;
				break;
			}
    		j++;
		}
		if (accept[j] == '\0')
			return (count);
		i++;
	}
	return (count);
}
//calcule la longueur de s qui est dans accept  

#include <string.h>
#include <stdio.h>
int	main(void)
{
	char s[] = "jHeallo a H ";
	char accept[] = " Heallo";

	printf("%ld\n", ft_strspn(s, accept));
	printf("%ld\n", strspn(s, accept));
	return (0);
}