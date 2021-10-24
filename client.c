#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void	exit_msg(int fd, char *str, int len, int status)
{
	write(fd, str, len);
	exit(status);
}

int	ft_atoi(const char *nptr)
{
	int	v;
	int	neg;

	v = 0;
	if (*nptr == '-' && nptr++)
		neg = 1;
	while (*nptr)
		if (*nptr >= '0' && *nptr <= '9')
			v = v * 10 - *nptr++ + '0';
		else
			exit_msg(2, "error: invalid pid\n", 19, 1);
	if (!v)
		exit_msg(2, "error: invalid pid\n", 19, 1);
	if (!neg)
		return (-v);
	return (v);
}

void	send_char(int pid, char c)
{
	int	n;

	n = 8;
	while (n--)
	{
		if (c & 1)
		{
			if (kill(pid, SIGUSR1))
				exit_msg(2, "error: invalid pid\n", 19, 1);
		}
		else if (kill(pid, SIGUSR2))
			exit_msg(2, "error: invalid pid\n", 19, 1);
		c >>= 1;
		pause();
	}
}

void	received(int sig)
{
	(void)sig;
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
		exit_msg(1, "usage: ./client [pid] [msg]\n", 28, 0);
	signal(SIGUSR1, received);
	pid = ft_atoi(argv[1]);
	while (*argv[2])
		send_char(pid, *argv[2]++);
	send_char(pid, 0);
	write(1, "msg received\n", 13);
}
