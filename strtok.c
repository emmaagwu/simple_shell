#include "shell.h"
/**
 *_strtok - tokenizes a string using delimiter
 *@str: the string to be tokenized
 *@delim: the delimiter str
 *Return: pointer to the token or NULL
 */

char *_strtok(char *str, const char *delim)
{
        static char *ptr;
        const char *d;

        if (str != NULL)
        {
                ptr = str;
        }
        else
        {
                if (*ptr == '\0')
                        return (NULL); /*End of string*/
                str = ptr;
        }
        while (*ptr != '\0')
        {
                d = delim;
                while (*d != '\0')
                {
                        if (*ptr == *d)
                        {
                                *ptr = '\0';
                                ptr++;
                                return (str);
                                /*break;*/
                        }
                        d++;
                }
                ptr++;
        }
        return (str);
}
