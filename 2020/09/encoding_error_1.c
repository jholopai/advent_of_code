#include <stdio.h>
#include <stdlib.h>

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
	int		*array;
	FILE	*file;

	i = 0;
	if (!(file = fopen("input.txt", "r")))
		return (0);
	if (!(array = (int*)malloc(sizeof(int) * rows)))
		return (0);
	while (i < rows)
	{
		fscanf(file, "%d", &array[i]);
		i++;
	}
	answer = decode(array, rows);
	fclose(file);
	return (answer);
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