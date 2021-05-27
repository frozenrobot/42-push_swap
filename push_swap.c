// Generic functions

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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

long	ft_atoi(char *str)
{
	long	multiply;
	long	size;
	int i;

	i = 0;
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

int valid_arg(char *str)
{
	int i;
	long int_min;
	long int_max;
	long num;

	i = 0;
	if (str[i] && (str[i] == '+' || str[i] == '-'))
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	if (i != ft_strlen(str))
		return (0);
	int_min = -2147483648;
	int_max = 2147483647;
	num = ft_atoi(str);
	// printf("num=%li\n", num);
	if (num > int_max || num < int_min)
		return (0);
	return (1);
}

/* ################################################################################################################# */

typedef struct	s_stack
{
	int				value;
	struct s_stack	*next;
	struct s_stack	*prev;
	int				index;
	int				valid;
}				t_stack;

void free_stack_list(t_stack *stack)
{
	t_stack *temp;

	temp = stack;
	while (temp->next->next)
		temp = temp->next;
	stack = temp->next; //stack is the last elem
	while (temp->prev)
	{
		temp->next = NULL;
		temp = temp->prev;
	}
	while (stack->prev)
	{
		temp = stack;
		stack = stack->prev;
		temp->prev = NULL;
		free(temp);
	}
	free(stack);
}

// void free_stack_cycle

t_stack *create_stack_elem(int num, int i)
{
	t_stack *elem;

	elem = malloc(sizeof(t_stack));
	if (!elem)
		return (NULL);
	elem->value = num;
	elem->index = i;
	elem->next = NULL;
	elem->prev = NULL;
	elem->valid = 1;
	return (elem);
}

t_stack *stack_add_back(t_stack *stack, int num, int i)
{
	t_stack *temp;
	t_stack *new;

	if (!stack)
		return (NULL);
	temp = stack;
	new = create_stack_elem(num, i);
	if (!new)
		free_stack_list(stack);
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
	return (stack);
}

t_stack *args_insert_stack(int ac, char *av[]) //handle stack size 1 or empty stack
{
	int i;
	t_stack *stack;
	t_stack *temp;

	stack = create_stack_elem(ft_atoi(av[1]), 1);
	if (!stack)
		return (NULL);
	i = 2;
	while (i < ac)
	{
		stack = stack_add_back(stack, ft_atoi(av[i]), i);
		i++;
	}
	temp = stack;
	while (temp->next)
		temp = temp->next;
	temp->next = stack;
	stack->prev = temp;
	return (stack);
}

t_stack *make_stack_b(int ac, char *av[])
{
	t_stack *stack;
	t_stack *temp;
	int i;

	stack = args_insert_stack(ac, av);
	temp = stack;
	i = 1;
	while (i < ac)
	{
		temp->valid = 0;
		temp = temp->next;
		i++;
	}
	return (stack);
}

void s(t_stack *stack, int argc)
{
	t_stack *temp;
	int store;

	temp = stack;
	while (temp->valid == 0 && temp->index != argc - 2) //argc - 2 is the second last element
		temp = temp->next;
	if (temp->index != argc - 1) //if 2nd last element or earlier (maybe dont need)
	{
		store = temp->value;
		temp->value = temp->next->value;
		temp->next->value = store;
	}
}

void pb(t_stack *stack_a, t_stack *stack_b)
{
	t_stack *temp;
	int store;

	temp = stack_a; //at the last index
	while (temp->valid == 0)
		temp = temp->next;
	store = temp->value;
	temp->valid = 0;
	temp = stack_b->prev;
	while (temp->valid == 1) //starting from bottom of stack, while full
		temp = temp->prev;
	temp->valid = 1;
	temp->value = store;	
}

void pa(t_stack *stack_a, t_stack *stack_b)
{
	t_stack *temp;
	int store;

	temp = stack_b; //at the last index
	while (temp->valid == 0)
		temp = temp->next;
	store = temp->value;
	temp->valid = 0;
	temp = stack_a->prev;
	while (temp->valid == 1) //starting from bottom of stack, while full
		temp = temp->prev;
	temp->valid = 1;
	temp->value = store;	
}

void r(t_stack *stack, int argc)
{
	t_stack *temp;
	int store;

	temp = stack;
	while (temp->valid == 0) //find first valid elem
		temp = temp->next;
	store = temp->value;
	while (temp->index != argc - 1)
	{
		temp->value = temp->next->value;
		temp = temp->next;
	}
	temp->value = store;
}

void rr(t_stack *stack)
{
	t_stack *temp;
	int store;

	temp = stack->prev;
	store = temp->value;
	while (temp->index != 1 && temp->prev->valid != 0)
	{
		temp->value = temp->prev->value;
		temp = temp->prev;
	}
	temp->value = store;
}

// typedef struct	s_int
// {
// 	int num;
// 	int valid;
// }				t_int;

// int *mem_plus_one_cpy(t_int *stack, int num)
// {
// 	t_int *new;
// }

// int *allocate_stack(int ac, char *av[]) //handle stack size 1 or empty stack
// {
// 	t_int i;
// 	t_int *stack[1];

// 	stack[0].num = ft_atoi(av[1]);
// 	stack[0].valid = 1;
// 	i = 2;
// 	while (i < ac)
// 	{
// 		mem_plus_one_cpy(stack, ft_atoi(av[i]));
// 	}
// }

int check_repetition(int ac, char *av[])
{
	int i;
	int j;
	int num;

	i = 1;
	while (i < ac - 1)
	{
		num = ft_atoi(av[i]);
		j = i + 1;
		while (j < ac)
		{
			if (num == ft_atoi(av[j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int input_isvalid(int ac, char *av[])
{
	int arg;

	arg = 1;
	if (ac < 2)
		return (0);
	while (arg < ac)
	{
		// printf("validarg=%i\n", valid_arg(av[arg]));
		if (!valid_arg(av[arg]))
			return (0);
		arg++;
	}
	if (check_repetition(ac, av))
		return (0);
	return (1);
}

int main(int argc, char *argv[])
{
	t_stack *stack_a;
	t_stack *stack_b;

	if (!input_isvalid(argc, argv))
	{
		ft_putstr("Error\n");
		return (1);
	}
	ft_putnbr(input_isvalid(argc, argv));
	printf("\n%i\n\n", argc);
	stack_a = args_insert_stack(argc, argv);
	stack_b = make_stack_b(argc, argv);
	t_stack *temp = stack_a;
	// for (int i = 1; i < argc; i++)
	// {
	// 	printf("A%i [%i]: %i\n", i, temp->valid, temp->value);
	// 	temp = temp->next;
	// }
	// temp = stack_b;
	// for (int j = 1; j < argc; j++)
	// {
	// 	printf("B%i [%i]: %i\n", j, temp->valid, temp->value);
	// 	temp = temp->next;
	// }
	pb(stack_a, stack_b); pb(stack_a, stack_b); pb(stack_a, stack_b);
	rr(stack_a);
	rr(stack_a);
	// rr(stack_a);
	temp = stack_a;
	for (int k = 1; k < argc; k++)
	{
		printf("rA%i [%i]: %i\n", k, temp->valid, temp->value);
		temp = temp->next;
	}
	// pb(stack_a, stack_b);
	// pb(stack_a, stack_b);
	// temp = stack_a;
	// for (int l = 1; l < argc; l++)
	// {
	// 	printf("pbA%i [%i]: %i\n", l, temp->valid, temp->value);
	// 	temp = temp->next;
	// }
	// temp = stack_b;
	// for (int m = 1; m < argc; m++)
	// {
	// 	printf("pbB%i [%i]: %i\n", m, temp->valid, temp->value);
	// 	temp = temp->next;
	// }
}