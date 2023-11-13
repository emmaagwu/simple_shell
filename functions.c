#include "shell.h"

/**
 *_getenv - gets a named environment variable
 *@name: the environment variable to get
 *@envp: array of environment variables
 *Return: NULL if env is unset or pointer to variable value
 */

char *_getenv(const char *name, char *envp[])
{
	char **env;
	char *current, *confirm;

	for (env = envp; *env != NULL; ++env)
	{
		current = *env;
		confirm = (char *)name;

		while (*current == *confirm && *current != '=')
		{
			current++;
			confirm++;
		}

		if (*current == '=' && *confirm == '\0')
		{
			return (current + 1);
		}
}
	return (NULL);
}

/**
 *tokenizer - tokenizes the command *
 *@cmd: the command to be tokenized
 *Return: the number of tokens from the command
 */

char  **tokenizer(char *cmd)
{
	char *token, *tmp = NULL;
	int count = 0, index = 0;
	char **argv = NULL;

	if (!cmd)
		return (NULL);
	tmp = my_strdup(cmd);
	token = strtok(tmp, DELIM);
	if (token == NULL)
	{
		free(tmp);
		return (NULL);
	}
	while (token)
	{
		count++;
		token = strtok(NULL, DELIM);
	}
	free(tmp);
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
	{
		free(argv);
		return (NULL);
	}
	token = strtok(cmd, DELIM);
	while (token != NULL)
	{
		argv[index] = token;
		token = strtok(NULL, DELIM);
		index++;
	}
	argv[index] = NULL;
	return (argv);
}

/**
 *path_const - constructs a path for command
 *@arg: array of tokens
 *@envp: array of environment variables
 *Return: pointer to the path
 */
char **path_const(char **arg, char *envp[])
{
	char *path_copy, *token, *dir;
	char path_cmd[100];
	int j, k;

	char *path = _getenv("PATH", envp);

	path_copy = my_strdup(path);
	token = strtok(path_copy, ":");
	while (token != NULL)
	{
	dir = token;
	token = strtok(NULL, ":");
	j = 0;
	while (dir[j] != '\0')
	{
		path_cmd[j] = dir[j];
		j++;
	}
	path_cmd[j++] = '/';
	k = 0;
	while (arg[0][k] != '\0')
	{
		path_cmd[j] = arg[0][k];
		j++;
		k++;
	}
	path_cmd[j] = '\0';
	if (access(path_cmd, X_OK) == 0)
	{
		arg[0] = path_cmd;
		break;
	}
	}
	free(path_copy);
	if (token == NULL)
	{
		return (NULL);
	}
	return (arg);
}

/**
 *print_error - prints the error message
 *@argv: the argument value
 *@cmd: the command
 *@i: the counter
 *Return: the string
 */

int print_error(char *argv[], char *cmd, int i)
{
	char *index =  _itoa(i);
	char *info = ": not found\n";

	write(STDERR_FILENO, argv[0], strlen(argv[0]));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, index, strlen(index));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, cmd, strlen(cmd));
	write(STDERR_FILENO, info, strlen(info));

	free(index);
	return (127);
}
