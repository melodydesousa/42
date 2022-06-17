int	*ft_range(int min, int max)
{
	int	*range;
	int	i;
	int	size;

	i = 0;
	size = max - min;
	if (min >= max)
		return (0);
	range = malloc(sizeof(int) * size);
	while (i < size)
	{
		range[i] = min;
		min++;
		i++;
	}
	return (range);
}