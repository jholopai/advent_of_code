#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 5

int		count_size()
{
	int		rows;
	FILE	*file;
	char	c;

	rows = 0;
	if (!(file = fopen("input.txt", "r")))
		return (0);
	while ((c = getc(file)) != EOF)
	{
		if (c == '\n')
			rows++;
	}
	fclose(file);
	return (rows);
}

int		*read_file(int size)
{
	int		i;
	int		*array;
	FILE	*file;

	i = 0;
	if (!(file = fopen("input.txt", "r")))
		return (0);
	if (!(array = (int*)malloc(sizeof(int) * size)))
		return (0);
	while (i < size)
	{
		fscanf(file, "%d", &array[i]);
		i++;
	}
	fclose(file);
	return (array);
}

int		*return_result(int index1, int index2)
{
	int *result;

	if (!(result = (int*)malloc(sizeof(int) * 2)))
		return (0);
	result[0] = index1;
	result[1] = index2;
	return (result);
}

int		*find_2020(int *array)
{
	int		i;
	int		i2;

	i = 0;
	i2 = 1;
	while (array[i])
	{
		while (array[i2])
		{
			if (i == i2)
				i2++;
			if ((array[i] + array[i2]) == 2020)
				return (return_result(i, i2));
			i2++;
		}
		i++;
		i2 = 0;
	}
	return (0);
}

int		main(void)
{
	int		size;
	int		*array;
	int		*result;
	int		first;
	int		second;

	if (!(size = count_size()))
		exit(EXIT_FAILURE);
	if (!(array = read_file(size)))
		exit(EXIT_FAILURE);
	if (!(result = find_2020(array)))
	{
		free(array);
		exit(EXIT_FAILURE);
	}
	first = result[0];
	second = result[1];
	free(array);
	free(result);
	printf("the answer is: %d\n", array[first] * array[second]);
	exit(EXIT_SUCCESS);
}