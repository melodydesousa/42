#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void	ft_putstr_fd(int fd, char *s)
{
	int i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	exec(int tmp_fd, int i, char **av, char **env)
{
	av[i] = NULL;
	dup2(tmp_fd, STDIN_FILENO);
	execve(av[0], av, env);
	ft_putstr_fd(STDERR_FILENO, "error: cannot execute ");
	ft_putstr_fd(STDERR_FILENO, av[0]);
	write(STDERR_FILENO, "\n", 1);
	return (1);
}

int main(int ac, char **av, char **env)
{
	int i = 0;
	int tmp_fd;
	int pipefd[2];

	(void)ac;
	tmp_fd = dup(STDIN_FILENO);
	while (av[i] && av[i + 1])
	{
		av = &av[i + 1];
		i = 0;
		while (av[i] && strcmp(av[i], ";") != 0 && strcmp(av[i], "|") != 0)
			i++;
		if (strcmp(av[0], "cd") == 0)
		{
			if (i != 2)
			{
				ft_putstr_fd(STDERR_FILENO, "error: cd: bad arguments");
				write(STDERR_FILENO, "\n", 1);
			}
			else if (chdir(av[1]) != 0)
			{
				ft_putstr_fd(STDERR_FILENO, "error: cd: cannot change directory to ");
				ft_putstr_fd(STDERR_FILENO, av[1]);
				write(STDERR_FILENO, "\n", 1);
			}
		}
		else if (i > 0 && (av[i] == NULL || strcmp(av[i], ";") == 0))
		{
			if (fork() == 0)
			{
				if (exec(tmp_fd, i, av, env) == 1)
					return (1);
			}
			else
			{
				close(tmp_fd);
				while (1)
				{
					if (waitpid(-1, NULL, 2) == -1)
						break ;
				}
				tmp_fd = dup(STDIN_FILENO);
			}
		}
		else if (i > 0 && strcmp(av[i], "|") == 0)
		{
			pipe(pipefd);
			if (fork() == 0)
			{
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[0]);
				close(pipefd[1]);
				if (exec(tmp_fd, i, av, env) == 1)
					return (1);
			}
			else
			{
				close(pipefd[1]);
				close(tmp_fd);
				tmp_fd = pipefd[0];
			}
		}
	}
	close(tmp_fd);
	return (0);
}