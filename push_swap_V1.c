// Generic functions

#include <unistd.h>
#include <stdio.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		ft_putchar(s[i]);
		i++;
	}
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

int		check_negative(int nb)
{
	if (nb < 0)
	{
		ft_putchar('-');
		nb = -nb;
	}
	return (nb);
}

void	ft_putnbr(int nb)
{
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	nb = check_negative(nb);
	if (nb > 9)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
		ft_putchar('0' + nb);
}

int ft_isspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\f' ||
		c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

int	check_size_ahead(char *str, int i)
{
	int	j;

	j = 0;
	while (str[i + j] <= '9' && str[i + j] >= '0')
	{
		j++;
	}
	return (j);
}

long	ten_power(int exp)
{
	if (exp == 0)
		return (1);
	return (10 * ten_power(exp - 1));
}

long	convert_to_int(char *str, int i, int size)
{
	long	result;
	int	j;

	result = 0;
	j = 1;
	while (j <= size)
	{
		result += ((str[i] - '0') * ten_power(size - j));
		i++;
		j++;
	}
	return ((long)result);
}

long	ft_atoi(char *str, int i)
{
	long	multiply;
	long	size;

	if (!str)
		return (0);
	multiply = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			multiply *= -1;
		i++;
	}
	size = check_size_ahead(str, i);
	return ((long)multiply * (long)convert_to_int(str, i, size));
}

int is_all_digit(char *str, int i)
{
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == '\0' || ft_isspace(str[i]))
		return (1);
	return (0);
}

/* Error code 20 */
int ft_digitlen(char *str, int i)
{
	int len;
	long int_min;
	long int_max;
	long num;

	len = 0;
	int_min = -2147483648;
	int_max = 2147483647;
	if (!is_all_digit(str, i))
		return (20);
	num = ft_atoi(str, i);
	if (num > int_max || num < int_min)
		return (20);
	if (str[i] == '+' || str[i] == '-')
		len++;
	while (str[i + len] >= '0' && str[i + len] <= '9')
		len++;
	return (len);
}

/* ################################################################################################################# */

int input_isvalid(int ac, char *av[])
{
	int i;
	int count;

	i = 0;
	count = 0;
	if (ac != 2)
		return (0);
	while (av[1][i])
	{
		// printf("i=%i\n", i);
		while(ft_isspace(av[1][i]))
			i++;
		if (av[1][i] && ft_digitlen(av[1], i))
		{
			// printf("digitlen=%i\n", count);
			if (ft_digitlen(av[1], i) == 20)
				return (0);
			i += ft_digitlen(av[1], i);
			count++;
			// printf("digitlen=%i\n", count);
		}
	}
	return (count);
}

int main(int argc, char *argv[])
{
	if (!input_isvalid(argc, argv))
	{
		ft_putstr("Error\n");
		return (1);
	}
	ft_putnbr(input_isvalid(argc, argv));
}