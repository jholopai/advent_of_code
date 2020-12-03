#include <stdlib.h>
#include <stdio.h>

int		error_handler(char **array, int rows)
{
	int i;

	i = 0;
	if (array != NULL)
	{
		while (i < rows)
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
	printf("Something went wrong.\n");
	exit(EXIT_FAILURE);
}

void	count_rows_and_length(int *rows, int *row_length)
{
	FILE	*file;
	char	c;

	if (!(file = fopen("input.txt", "r")))
			error_handler(NULL, *rows);
	*rows = 0;
	*row_length = 0;
	while ((c = getc(file)) != EOF)
	{
		if (*rows == 0 && c != '\n')
			*row_length = *row_length + 1;
		if (c == '\n')
			*rows = *rows + 1;
	}
	fclose(file);
}

char	**read_file(int rows, int row_length)
{
	int		i;
	char	**array;
	FILE	*file;

	i = 0;
	if (!(file = fopen("input.txt", "r")))
		error_handler(NULL, rows);
	if (!(array = (char**)malloc(sizeof(char*) * rows + 1)))
		error_handler(NULL, rows);
	while (i < rows)
	{
		if (!(array[i] = (char*)malloc(row_length * sizeof(char) + 1)))
			error_handler(array, i);
		fscanf(file, "%s", array[i]);
		i++;
	}
	fclose(file);
	return (array);
}

int		count_trees(char **array, int rows, int row_length)
{
	int		x;
	int		y;
	int		trees;

	x = 0;
	y = 0;
	trees = 0;
	while (y < rows - 1)
	{
		y++;
		x += 3;
		if (x >= row_length)
			x = x - row_length;
		if (array[y][x] == '#')
			trees++;
	}
	return (trees);
}

int		main(void)
{
	int		rows;
	int		row_length;
	int		answer;
	char	**array;

	count_rows_and_length(&rows, &row_length);
	array = read_file(rows, row_length);
	answer = count_trees(array, rows, row_length);
	printf("answer is: %d\n", answer);
	exit(EXIT_SUCCESS);
}