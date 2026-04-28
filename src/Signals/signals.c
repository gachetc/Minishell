#include "minishell.h"

int	set_signal_handling(t_shell *shell)
{
	sigemptyset(&shell->sigset);
	sigaddset(&shell->sigset, SIGINT);
	sigaddset(&shell->sigset, SIGQUIT);
	shell->sigactions.sa_handler = signal_handler;
	shell->sigactions.sa_mask = shell->sigset;
	shell->sigactions.sa_flags = 0;
	if (sigaction(SIGINT, &shell->sigactions, NULL) == -1)
	{
		error("set_signal_handling: SIGINT", NULL);
		return (1);
	}
	if (sigaction(SIGQUIT, &shell->sigactions, NULL) == -1)
	{
		error("set_signal_handling: SIGQUIT", NULL);
		return (1);
	}
	return (0);
}

int	set_termios(t_shell *shell)
{
	if (tcgetattr(STDIN_FILENO, &shell->original_termios))
	{
		error("set_termios: tcgetattr", NULL);
		return (1);
	}
	shell->updated_termios = shell->original_termios;
	shell->updated_termios.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &shell->updated_termios))
	{
		error("set_termios: tcsetattr", NULL);
		return (1);
	}
	return (0);
}

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		if (RL_ISSTATE(RL_STATE_EOF) || RL_ISSTATE(RL_STATE_DONE))
			return ;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
		rl_redisplay();
}

void	reset_signal_handlers(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
