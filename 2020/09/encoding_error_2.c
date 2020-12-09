#include <stdio.h>
#include <stdlib.h>

int		error_handler()
{
	printf("Something went wrong.\n");
	exit(EXIT_FAILURE);
}

int		count_rows()
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

int		decode2(int *array, int rows, int key)
{
	int		i;
	int		p;
	int		sum;
	int		biggest;
	int		smallest;

	i = 0;
	sum = 0;
	while (i < rows)
	{
		p = i;
		smallest = 2147483647;
		biggest = 0;
		while (sum < key)
		{
			sum += array[p];
			if (array[p] > biggest)
				biggest = array[p];
			if (array[p] < smallest)
				smallest = array[p];
			if (sum == key)
				return (smallest + biggest);
			p++;
		}
		sum = 0;
		i++;
	}
	return (0);
}

int		decode(int *array, int rows)
{
	int		i;
	int		p;
	int		still;

	i = 25;
	while (i < rows)
	{
		still = i - 25;
		while (still < i)
		{
			p = i - 24;
			while (p < i)
			{
				if (still == p)
					p++;
				if (array[still] + array[p] == array[i])
				{
					still = i;
					break ;
				}
				p++;
			}
			if (still == i - 1)
				return (array[i]);
			still++;
		}
		i++;
	}
	return (0);
}

int		read_file(int rows)
{
	int		i;
	int		answer;
	int		answer2;
	int		*array;
	FILE	*file;

	i = 0;
	if (!(file = fopen("input.txt", "r")))
		return (error_handler());
	if (!(array = (int*)malloc(sizeof(int) * rows)))
		return (error_handler());
	while (i < rows)
	{
		fscanf(file, "%d", &array[i]);
		i++;
	}
	answer = decode(array, rows);
	answer2 = decode2(array, rows, answer);
	free(array);
	fclose(file);
	return (answer2);
}

int		main()
{
	int		rows;
	int		answer;

	rows = count_rows();
	answer = read_file(rows);
	printf("answer is: %d\n", answer);
	exit(EXIT_SUCCESS);
}