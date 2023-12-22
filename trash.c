#include "include/pipex.h"

void	exec_pipex(t_pipex *p, int i)
{
	pid_t	ppid;

	if (pipe(pipe_end) < 0)
		return (clean_pipex(*p), perror("Pipe"), exit(1));
	ppid = fork();
	if (ppid < 0)
		return (clean_pipex(*p), perror("Fork"), exit(1));
	if (!ppid)
		child_pid(p, i, pipe_end);
	else
		parent_ppid(p, i, pipe_end);
}

void	pipex(int ac, char **av, char **env)
{
	pid_t	pid1;
	pid_t	pid2;
	int		i;

	i = 0;
	pid1 = fork();
	if (pid1 == 0)
		child_pid(&p, i);
	// exec_in_path(p.command_path, p.command_args[0], env);
	// if (dup2(p.fd_in, STDIN_FILENO) < 0)
	// 	return (clean_pipex(p), perror("Dup2"), exit(1));
	clean_pipex(&p);
	// exec_in_path(p.command_path, av[2], p.command_args[0], env);
}

// child pid :
if	(dup2(pipend[STDOUT_FILENO], STDOUT_FILENO) < 0)
	return (clean_pipex(*p),
			perror("Dup2"),
			exit(1));

if	(dup2(pipend[STDIN_FILENO], STDIN_FILENO))
	return (clean_pipex(*p), perror("Dup2"), exit(1));
if	(dup2(p.fd_out, STDOUT_FILENO) < 0)
	return (clean_pipex(p), perror("Dup2"), exit(1));

exec_in_path(p->command_path, p->command_args[i], p->env);


void	errors_holder_fd(t_pipex *p, char *file_in, char *file_out)
{
	int	bool_err;

	bool_err = 0;
	if (p->fd_in == -1)
		return ((void)ft_printfd(STDERR, "%s: %s\n", file_in, p->err_fd_in), clean_pipex(p), exit(SUCCESS));
	if (p->fd_out == -1)
		return((void)ft_printfd(STDERR, "%s: %s\n", file_out, p->err_fd_out), clean_pipex(p), exit(SUCCESS));
}

	// if (!WIFEXITED(p->child_wstatus))
	// 	exit(WEXITSTATUS(p->child_wstatus));


// Parsing

		cmd_in_path = join_cmd(p->cmd_args[cmd][0], p->cmd_path[i]);
		if (!cmd_in_path)
			return (free(cmd_in_path), clean_pipex(p), perror("Malloc"),
				exit(errno));
		free(cmd_in_path);