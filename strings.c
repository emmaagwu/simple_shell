#include "shell.h"

/**
 *my_strdup - duplicates a string
 *@str: the string to be duplicated
 *Return: pointer to the string
 */

char *my_strdup(const char *str)
{
	char *dup_str;
	/*char *new_str;*/
	int i, len = 0;
	/*Calculate the length of the string */
	while (str[len] != '\0')
	{
		len++;
	}

	/* Allocate memory for the new string */
	dup_str = (char *)malloc(len + 1);

	if (dup_str == NULL)
		return (NULL);

	/* Copy the string character by character */
	for (i = 0; i <= len; i++)
		dup_str[i] = str[i];

return (dup_str);
}


/**
 *rev_string - reverses a string
 *@s: the string to be reversed
 *
 *Return: void
 */

void rev_string(char *s)
{
	int i, temp, len;

	for (i = 0; *(s + i) != '\0';)
	{
		i++;
	}
	len = i - 1;

	for (i = 0; i <= len / 2; i++)
	{
		temp = s[i];
		s[i] = s[len - i];
		s[len - i] = temp;
	}
}

/**
  *_itoa - changes int to str
  *@n: the int to be converted
  *Return: the string
  */

char *_itoa(int n)
{
	char buff[20];
	int i = 0;

	if (n == 0)
		buff[i++] = '0';
	else
	{
		while (n > 0)
		{
			buff[i++] = (n % 10) + '0';
			n /= 10;
		}
	}
	buff[i] = '\0';
	rev_string(buff);
	return (my_strdup(buff));

}
