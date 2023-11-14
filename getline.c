#include "shell.h"

/**
 *_getline - custom getline function
 *@cmd: the pointer to the line pointer
 *@cmd_len: the pointer to the byte read
 *@stream: i/o stream
 *Return: -1 or pointer to the cmd
 */

int _getline(char **cmd, size_t *cmd_len, FILE *stream)
{
        static char buff[BUFFER_SIZE];
        static size_t i, bsize;
        int count = 0;
        char c;

        if (!*cmd || *cmd_len < BUFFER_SIZE)
        {
                if (allocate_buffer(cmd, cmd_len) == -1)
                        return (-1);
        }

        while (1)
        {
                if (i == bsize)
                {
                        if (fill_buffer(stream, buff, &bsize) == -1)
                        {
                                if (count != 0)
                                        return (count);
                                else
                                        return (-1);
                        }

                i = 0;
                }
                c = buff[i++];
                (*cmd)[count++] = c;
                if (c == '\n' || count >= BUFFER_SIZE - 1)
                        break;
        }

        if (count)
                (*cmd)[count] = '\0';

        return (count);
}

/**
 *allocate_buffer - allocates new buffer
 *@cmd: the command input
 *@cmd_len: the length of command
 *Return: 0
 */

int allocate_buffer(char **cmd, size_t *cmd_len)
{
        char *new_cmdptr = (char *)malloc(BUFFER_SIZE);

        if (!new_cmdptr)
        {
                free(*cmd);
                        return (-1);
        }
                free(*cmd);  /*Free the old buffer*/
                *cmd = new_cmdptr;
                *cmd_len = BUFFER_SIZE;

        return (0);
}

/**
 *fill_buffer - fills the buffer
 *@stream: the i/0 stream
 *@buff: to store the input
 *@bsize: the aize of buffer
 *Return:0
 */
int fill_buffer(FILE *stream, char *buff, size_t *bsize)
{
        ssize_t bytesRead = read(fileno(stream), buff, BUFFER_SIZE);

        if (bytesRead <= 0)
                return (bytesRead);

        *bsize = bytesRead;
        return (0);
}
