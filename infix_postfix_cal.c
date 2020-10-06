#include <stdio.h>
#include <ctype.h>

int count_alphabets(char* str)
{
	int count = 0;
	while (*(str + count)) count++;
	return count;
}
int main()
{
	char str[30];

	gets_s(str, 30);

	puts(str);
	exit(0);
	printf("%d", count_alphabets(str));

	return 0;
}