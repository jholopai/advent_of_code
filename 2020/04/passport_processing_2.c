#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LENGTH 100

struct	Checks {
	int		byr;
	int		iyr;
	int		eyr;
	int		hgt;
	int		hcl;
	int		ecl;
	int		pid;
	int		cid;
};

void	reset_passp_fields(struct Checks *passp_fields)
{
	passp_fields->byr = 0;
	passp_fields->iyr = 0;
	passp_fields->eyr = 0;
	passp_fields->hgt = 0;
	passp_fields->hcl = 0;
	passp_fields->ecl = 0;
	passp_fields->pid = 0;
	passp_fields->cid = 0;
}

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

int		check_fields(struct Checks *passp_fields)
{
	if (passp_fields->byr == 1 && passp_fields->iyr == 1 && passp_fields->eyr == 1\
	&& passp_fields->hgt == 1 && passp_fields->hcl == 1 && passp_fields->ecl == 1\
	&& passp_fields->pid == 1)
		return (1);
	else
		return (0);
}

int		check_validity(int field, int index, char line[MAX_LENGTH])
{
	int		i;
	int		round;
	int		number;
	int		inch_or_cm;

	i = index + 4;
	round = 0;
	inch_or_cm = 0;
	if (field == 1)
	{
		number = atoi(line + i);
		if (number >= 1920 && number <= 2002)
			return (1);
	}
	if (field == 2)
	{
		number = atoi(line + i);
		if (number >= 2010 && number <= 2020)
			return (1);
	}
	if (field == 3)
	{
		number = atoi(line + i);
		if (number >= 2020 && number <= 2030)
			return (1);
	}
	if (field == 4)
	{
		number = atoi(line + i);
		if (strnstr(line + i + nbrlen(number), "cm", 4))
			inch_or_cm = 'c';
		if (strnstr(line + i + nbrlen(number), "in", 3))
			inch_or_cm = 'i';
		if (inch_or_cm == 'c' && number >= 150 && number <= 193)
			return (1);
		if (inch_or_cm == 'i' && number >= 59 && number <= 76)
			return (1);
	}
	if (field == 5)
	{
		if (line[i] != '#')
			return (0);
		i++;
		while (round < 6)
		{
			if (!(isdigit(line[i])) && (!(isalpha(line[i]))))
				return (0);
			i++;
			round++;
		}
		if ((isdigit(line[i])) || (isalpha(line[i])))
			return (0);
		else
			return (1);
	}
	if (field == 6)
	{
		if ((strnstr(line + i, "amb", 4)) || (strnstr(line + i, "blu", 4)) || (strnstr(line + i, "brn", 4))\
		|| (strnstr(line + i, "gry", 4)) || (strnstr(line + i, "grn", 5)) || (strnstr(line + i, "hzl", 4)) \
		|| (strnstr(line + i, "oth", 4)))
			return (1);
	}
	if (field == 7)
	{
		number = atoi(line + i);
		while (round < 9)
		{
			if (!(isdigit(line[i])))
				return (0);
			i++;
			round++;
		}
		if ((isdigit(line[i])))
			return (0);
		return (1);
	}
	return (0);
}

void	check_line(char line[MAX_LENGTH], struct Checks *passp_fields)
{
	int		index;
	char	*pointer;

	index = 0;
	if ((pointer = strstr(line, "byr")))
	{
		index = pointer - line;
		if (check_validity(1, index, line) == 1)
			passp_fields->byr = 1;
	}
	if ((pointer = strstr(line, "iyr")))
	{
		index = pointer - line;
		if (check_validity(2, index, line) == 1)
			passp_fields->iyr = 1;
	}
	if ((pointer = strstr(line, "eyr")))
	{
		index = pointer - line;
		if (check_validity(3, index, line) == 1)
			passp_fields->eyr = 1;
	}
	if ((pointer = strstr(line, "hgt")))
	{
		index = pointer - line;
		if (check_validity(4, index, line) == 1)
			passp_fields->hgt = 1;
	}
	if ((pointer = strstr(line, "hcl")))
	{
		index = pointer - line;
		if (check_validity(5, index, line) == 1)
			passp_fields->hcl = 1;
	}
	if ((pointer = strstr(line, "ecl")))
	{
		index = pointer - line;
		if (check_validity(6, index, line) == 1)
			passp_fields->ecl = 1;
	}
	if ((pointer = strstr(line, "pid")))
	{
		index = pointer - line;
		if (check_validity(7, index, line) == 1)
			passp_fields->pid = 1;
	}
	if ((strstr(line, "cid")))
		passp_fields->cid = 1;
}

int		read_file(int rows)
{
	int		i;
	int		valids;
	char	line[MAX_LENGTH];
	FILE	*file;

	struct Checks *passp_fields;
	if (!(passp_fields = (struct Checks*)malloc(sizeof(passp_fields))))
		error_handler();
	reset_passp_fields(passp_fields);
	if (!(file = fopen("input.txt", "r")))
		error_handler();
	i = 0;
	valids = 0;
	while (i < rows)
	{
		fgets(line, MAX_LENGTH, file);
		if (line[0] == '\n')
		{
			if (check_fields(passp_fields) == 1)
				valids++;
			reset_passp_fields(passp_fields);
		}
		else
			check_line(line, passp_fields);
		memset(line, '\0', MAX_LENGTH);
		i++;
	}
	if (check_fields(passp_fields) == 1)
		valids++;
	free(passp_fields);
	fclose(file);
	return (valids);
}

int		main(void)
{
	int		rows;
	int		answer;

	rows = count_rows();
	answer = read_file(rows);
	printf("answer is: %d\n", answer);
	exit(EXIT_SUCCESS);
}