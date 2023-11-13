#include "shell.h"

/**
 *exit_shell - exits the shell
 *@argv: command line argumen
 *
 */

void exit_shell(char *argv[])
{
	int status;
	char *str;

	printf("check\n");
	str = argv[1];
	printf("%s", str);

	status = atoi(str);

	if (status != 0)
		exit(status);
	else
		exit(EXIT_SUCCESS);
}

/**
 *print_env - prints the environmental variables
 *@envp: prints the environmental variables
 *
 */

void print_env(char *envp[])
{
	int i;

	for (i = 0; envp[i]; i++)
	{
		write(STDOUT_FILENO, envp[i], strlen(envp[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
}


/**
 *executor - checks and execute a command
 *@arg: the command to be executed
 *@envp: the environment variable
 *Return: the correct exit status
 */
int executor(char **arg, char *envp[])
{
	pid_t child_pid;
	int status;

	if (strcmp(arg[0], "exit") == 0)
		exit(EXIT_SUCCESS);
	if (access(arg[0], X_OK) == -1)
	{
		arg = path_const(arg, envp);
		if (arg == NULL)
			return (-1);
	}
	child_pid = fork();
	if (child_pid < 0)
	{
		perror("fork");
	}
	else if (child_pid == 0)
	{
		if (execve(arg[0], arg, envp) == -1)
		{
			perror("execve");
			exit(0);
		}
	}
	else
	{
		waitpid(child_pid, NULL, 0);
	}
	free(arg), arg = NULL;
	return (WEXITSTATUS(status));
}



/**
 *main - the shell entry point
 *@argc: the number of main arguments
 *@argv: the list of main argument
 *@envp: the environmental variable
 *Return: 0 when successful
 */

int main(int argc, char *argv[], char *envp[])
{
	char *prompt = "$ ";
	char **arg = NULL, *cmd = NULL;
	size_t cmd_len = 0;
	ssize_t charRead;
	int ind = 0, status;

	(void)argc;
	while (true)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		charRead = getline(&cmd, &cmd_len, stdin);
		if (charRead == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			free(cmd);
			return (0);
		}
		ind++;
		arg = tokenizer(cmd);
		if (!arg)
			continue;
		if (strcmp(arg[0], "env") == 0)
			print_env(envp);
		else if (executor(arg, envp) == -1)
			status = print_error(argv, cmd, ind);
	}
	free(cmd), cmd = NULL;
	return (status);
}
