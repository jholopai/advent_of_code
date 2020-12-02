#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 50

int		nbrlen(int nr)
{
	int i;

	i = 1;
	while (nr >= 10 || nr <= -10)
	{
		nr /= 10;
		i++;
	}
	if (nr < 0)
		i++;
	return (i);
}


int		check_line(char *line)
{
	int		i;
	int		min;
	int		max;
	int		min_len;
	int		max_len;
	int		chars_found;
	char	character;

	min = atoi(line);
	min_len = nbrlen(min);
	max = atoi(line + min_len + 1);
	max_len = nbrlen(max);
	character = line[min_len + max_len + 2];
	i = min_len + max_len + 5;
	chars_found = 0;
	while (line[i] != '\0')
	{
		if (line[i] == character)
			chars_found++;
		i++;
	}
	if (chars_found >= min && chars_found <= max)
		return (1);
	else
		return (0);
}

int		read_input(void)
{
	int		corrects;
	char	line[MAX_LENGTH];
	char	*temp;
	FILE	*file;

	corrects = 0;
	if (!(file = fopen("input.txt", "r")))
		return (0);
	while (fgets(line, MAX_LENGTH, file) != NULL)
	{
		if (!(temp = strdup(line)))
			return (-1);
		if (check_line(temp) == 1)
			corrects++;
		free(temp);
	}
	fclose(file);
	return (corrects);
}

int		main(void)
{
	int answer;

	answer = read_input();
	if (answer == -1)
	{
		printf("Something has gone wrong.\n");
		exit(EXIT_FAILURE);
	}
	printf("answer is: %d", answer);
	exit(EXIT_SUCCESS);
}