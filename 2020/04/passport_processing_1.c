#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

void	check_line(char line[MAX_LENGTH], struct Checks *passp_fields)
{
	if (strstr(line, "byr"))
		passp_fields->byr = 1;
	if (strstr(line, "iyr"))
		passp_fields->iyr = 1;
	if (strstr(line, "eyr"))
		passp_fields->eyr = 1;
	if (strstr(line, "hgt"))
		passp_fields->hgt = 1;
	if (strstr(line, "hcl"))
		passp_fields->hcl = 1;
	if (strstr(line, "ecl"))
		passp_fields->ecl = 1;
	if (strstr(line, "pid"))
		passp_fields->pid = 1;
	if (strstr(line, "cid"))
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