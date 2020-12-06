#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

int		error_handler()
{
	printf("Something went wrong.\n");
	exit(EXIT_FAILURE);
}

int		count_rows()
{
	int		rows;
	char	c;
	FILE	*file;

	if (!(file = fopen("input.txt", "r")))
			error_handler();
	rows = 0;
	while ((c = getc(file)) != EOF)
	{
		if (c == '\n')
			rows++;
	}
	fclose(file);
	return (rows);
}

char	*strjoin(char const *s1, char const *s2)
{
	int		i;
	int		len1;
	int		len2;
	char	*result;

	if (s1 && s2)
	{
		i = -1;
		len1 = strlen(s1);
		len2 = strlen(s2);
		if (!(result = (char*)malloc(len1 + len2 * sizeof(char) + 1)))
			return (NULL);
		while (s1[++i] != '\0')
			result[i] = s1[i];
		while (*s2 != '\0')
		{
			result[i++] = *s2;
			s2++;
		}
		result[i] = '\0';
		return (result);
	}
	return (NULL);
}


int		count_uniques(char *group, int members)
{
	int		i;
	int		uniques;
	int		character;
	int		chars_found;

	i = 0;
	uniques = 0;
	character = 'a';
	chars_found = 0;
	while (character <= 'z')
	{
		while (group[i] != '\0')
		{
			if (group[i] == character)
				chars_found++;
			i++;
		}
		if (chars_found == members)
			uniques++;
		i = 0;
		character++;
		chars_found = 0;
	}
	return (uniques);
}

int		read_file(int rows)
{
	int		i;
	int		members;
	int		uniques;
	char	*temp;
	char	*group;
	char	line[MAX_LENGTH];
	FILE	*file;

	if (!(file = fopen("input.txt", "r")))
		error_handler();
	i = 0;
	members = 0;
	uniques = 0;
	group = NULL;
	while (i < rows)
	{
		fgets(line, MAX_LENGTH, file);
		if (line[0] != '\n')
		{
			if (!(group))
				group = strdup(line);
			else
			{
				temp = strjoin(group, line);
				free(group);
				group = strdup(temp);
				free(temp);
			}
			members++;
		}
		else
		{
			uniques += count_uniques(group, members);
			free(group);
			group = NULL;
			members = 0;
		}
		i++;
	}
	uniques += count_uniques(group, members);
	free(group);
	fclose(file);
	return (uniques);
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