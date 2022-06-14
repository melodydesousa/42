char	*ft_strrev(char *str)
{
	int	j;
	int	i;
	char	tmp;

	j = 0;
	i = 0;
	while (str[j])
		j++;
	while (i < j - 1)
	{
		tmp = str[i];
		str[i] = str[j - 1];
		str[j - 1] = tmp;
		i++;
		j--;
	}
	return (str);
}


#include <stdio.h>
int	main(void)
{
	char s[] = "Hello World";
	ft_strrev(s);
	printf("%s\n", s);
	return (0);
}