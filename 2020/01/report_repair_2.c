#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 5

int		error_handler(int *array)
{
	if (array)
		free(array);
	printf("Something went wrong.\n");
	exit(EXIT_FAILURE);
}

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

int		*return_result(int index1, int index2, int index3)
{
	int *result;

	if (!(result = (int*)malloc(sizeof(int) * 3)))
		return (0);
	result[0] = index1;
	result[1] = index2;
	result[2] = index3;
	return (result);
}

int		*find_2020(int *array)
{
	int		i;
	int		i2;
	int		i3;

	i = 0;
	i2 = 1;
	i3 = 2;
	while (array[i])
	{
		while (array[i2])
		{
			if (i2 == i)
				i2++;
			while (array[i3])
			{
				if (i3 == i2 || i3 == i)
					i3++;
				if ((array[i] + array[i2] + array[i3]) == 2020)
					return (return_result(i, i2, i3));
				i3++;
			}
			i2++;
			i3 = 0;
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
	int		third;

	if (!(size = count_size()))
		return (error_handler(0));
	if (!(array = read_file(size)))
		return (error_handler(0));
	if (!(result = find_2020(array)))
		return (error_handler(array));
	first = result[0];
	second = result[1];
	third = result[2];
	free(array);
	free(result);
	printf("the answer is: %d\n", array[first] * array[second] * array[third]);
	exit(EXIT_SUCCESS);
}