#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

typedef struct s_data_signal
{
	char	byte;
	int		i;
}	t_data_signal;

t_data_signal	g_data_signal = {0, 0};

void	print_pid()
{
	pid_t		n;
	int			i;
	static char	res[10];

	write(1, "pid: ", 5);
	n = getpid();
	if (n < 0)
		write(1, "-", 1);
	else
		n = -n;
	i = 10;
	while (1)
	{
		res[--i] = '0' - n % 10;
		n /= 10;
		if (!n)
			break ;
	}
	write(1, res + i, 10 - i);
	write(1, "\n", 1);
}

void	receive_bit(int bit, siginfo_t *info, void *ctx)
{
	(void)ctx;
	if (bit == SIGUSR1)
		bit = 1;
	else
		bit = 0;
//	write(1, bit ? "1" : "0", 1);
	g_data_signal.byte |= bit << g_data_signal.i++;
	if (g_data_signal.i == 8)
	{
		g_data_signal.i = 0;
		if (g_data_signal.byte)
			write(1, &g_data_signal.byte, 1);
		else
			write(1, "\n", 1);
		g_data_signal.byte = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	bit0;
	struct sigaction	bit1;

	bit0.sa_flags = SA_SIGINFO;
	bit0.sa_sigaction = receive_bit;
	bit1.sa_flags = SA_SIGINFO;
	bit1.sa_sigaction = receive_bit;
	print_pid();
	sigaction(SIGUSR1, &bit0, NULL);
	sigaction(SIGUSR2, &bit1, NULL);
	while (1)
		pause();
}
