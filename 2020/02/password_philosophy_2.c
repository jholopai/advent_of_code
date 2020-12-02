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
	int		first;
	int		second;
	int		first_len;
	int		second_len;
	char	character;

	first = atoi(line);
	first_len = nbrlen(first);
	second = atoi(line + first_len + 1);
	second_len = nbrlen(second);
	character = line[first_len + second_len + 2];
	first--;
	second--;
	i = first_len + second_len + 5;
	if (line[i + first] == character && line[i + second] != character)
		return (1); 
	if (line[i + first] != character && line[i + second] == character)
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
	return (0);
}