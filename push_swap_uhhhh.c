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

void free_stack_list(t_stack *stack) //unverified
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

void free_stack_cycle(t_stack *stack, int argc) //unverified
{
	t_stack *temp;

	temp = stack;
	while (temp->index != argc - 1)
	{
		temp->prev = NULL;
		temp = temp->next;
	}
	temp->prev = NULL;
	temp->next = NULL;
	temp = stack;
	while (stack->index != argc - 1)
	{
		stack = stack->next;
		temp->next = NULL;
		free(temp);
		temp = stack;
	}
	free(temp);
}

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

t_stack *zero_insert_stack(int ac) //handle stack size 1 or empty stack
{
	int i;
	t_stack *stack;
	t_stack *temp;

	stack = create_stack_elem(0, 1);
	if (!stack)
		return (NULL);
	i = 2;
	while (i < ac)
	{
		stack = stack_add_back(stack, 0, i);
		i++;
	}
	temp = stack;
	while (temp->next)
		temp = temp->next;
	temp->next = stack;
	stack->prev = temp;
	return (stack);
}

void set_invalid(t_stack *stack, int ac)
{
	int i;
	t_stack *temp;

	i = 1;
	temp = stack;
	while (i < ac)
	{
		temp->valid = 0;
		temp = temp->next;
		i++;
	}
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

void sa(t_stack *stack_a, int argc)
{
	s(stack_a, argc);
	ft_putstr("sa\n");
}

void sb(t_stack *stack_b, int argc)
{
	s(stack_b, argc);
	ft_putstr("sa\n");
}

void ss(t_stack *stack_a, t_stack *stack_b, int argc)
{
	s(stack_a, argc);
	s(stack_b, argc);
	ft_putstr("ss\n");
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
	ft_putstr("pb\n");	
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
	ft_putstr("pa\n");	
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

void ra(t_stack *stack_a, int argc)
{
	r(stack_a, argc);
	ft_putstr("ra\n");
}

void rb(t_stack *stack_b, int argc)
{
	r(stack_b, argc);
	ft_putstr("rb\n");
}

void rr(t_stack *stack_a, t_stack *stack_b, int argc)
{
	r(stack_a, argc);
	r(stack_b, argc);
	ft_putstr("rr\n");
}

void rrab(t_stack *stack)
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

void rra(t_stack *stack_a)
{
	rrab(stack_a);
	ft_putstr("rra\n");
}

void rrb(t_stack *stack_b)
{
	rrab(stack_b);
	ft_putstr("rrb\n");
}

void rrr(t_stack *stack_a, t_stack *stack_b)
{
	rrab(stack_a);
	rrab(stack_b);
	ft_putstr("rrr\n");
}

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
		if (!valid_arg(av[arg]))
			return (0);
		arg++;
	}
	if (check_repetition(ac, av))
		return (0);
	return (1);
}

int is_ascending_a(t_stack *stack, int ac)
{
	t_stack *temp;
	int i;

	i = 1;
	temp = stack;
	while (i++ < ac && temp->valid == 0)
		temp = temp->next;
	while (i++ < ac - 1)
	{
		if (temp->next->value < temp->value)
			return (0);
		temp = temp->next;	
	}
	return (1);
}

// int is_descending_b(t_stack *stack, )
// {
// 	t_stack *temp;
// 	int i;

// 	i = 1;
// 	temp = stack;
// 	while (i++ < ac && temp->valid == 0)
// 		temp = temp->next;
// 	while (i++ < ac - 1)
// 	{
// 		if (temp->next->value > temp->value)
// 			return (0);
// 		temp = temp->next;	
// 	}
// 	return (1);
// }

int is_sort_a(t_stack *stack, int ac)
{
	int i;
	t_stack *temp;

	i = 1;
	temp = stack;
	if (temp->valid == 0)
		return (0);
	while (i < ac - 1)
	{
		temp = temp->next;
		if (temp->valid == 0 || temp->value < temp->prev->value)
			return (0);
		i++;
	}
	return (1);
}



// void insertion_sort(t_stack *stack_a, t_stack *stack_b, int ac)
// {
// 	int min;
// 	int i;
// 	int j;
// 	t_stack *temp;

// 	j = 1;
// 	while (j < ac)
// 	{
// 		i = 1;
// 		temp = stack_a;
// 		while (temp->valid != 1)
// 			temp = temp->next;
// 		min = temp->value;
// 		temp = stack_a;
// 		while (i < ac)
// 		{
// 			temp = temp->next;
// 			if (temp->valid == 1 && temp->value < min)
// 				min = temp->value;
// 			i++;
// 		}
// 		while (stack_a->prev->valid == 1 && stack_a->prev->value != min)
// 			rra(stack_a);
// 		rra(stack_a);
// 		pb(stack_a, stack_b);
// 		j++;	
// 	}
// 	j = 1;
// 	while (j < ac)
// 	{
// 		pa(stack_a, stack_b);
// 		j++;
// 	}
// }

// void unruled_insertion_sort(t_stack *stack, int ac, int i, int min) // i = 1, min = 0; // WEIRD VERSION
// {
// 	t_stack *temp;
// 	t_stack *temp2;
// 	int j;

// 	temp = stack;
// 	while (i < ac - 1 && temp->valid == 0)
// 	{
// 		temp = temp->next;
// 		i++;
// 	}
// 	while (i < ac)
// 	{
// 		temp2 = temp;
// 		min = temp2->value;
// 		j = i;
// 		while (j < ac)
// 		{
// 			temp2 = temp2->next;
// 			if (temp2->value < min)
// 			{
// 				temp->value = temp2->value;
// 				temp2->value = min;
// 				min = temp->value;
// 			}
// 			j++;
// 		}
// 		temp = temp->next;
// 		i++;
// 	}
// }

void unruled_insertion_sort(t_stack *stack, int ac, int i, int min)
{
	t_stack *temp;
	t_stack *temp2;

	temp = stack;
	temp->prev = NULL;
	while (i++ < ac - 1)
		temp = temp->next;
	temp->next = NULL;
	temp = stack;
	while (temp->valid == 0)
		temp = temp->next;
	while (temp->next)
	{
		temp2 = temp;
		min = temp2->value;
		while (temp2->next)
		{
			temp2 = temp2->next;
			if (temp2->value < min)
			{
				temp->value = temp2->value;
				temp2->value = min;
				min = temp->value;
			}
		}
		temp = temp->next;
	}
}

int valid_count(t_stack *stack, int ac)
{
	int i;
	t_stack *temp;
	int count;

	i = 1;
	count = 0;
	temp = stack;
	while (i < ac && temp->valid == 0)
	{
		temp = temp->next;
		i++;
	}
	while (i < ac && temp->valid != 0)
	{
		count++;
		temp = temp->next;
		i++;
	}
	return (count);
}

int valid_count_a_top(t_stack *stack, int mid, int ac)
{
	int i;
	t_stack *temp;
	int count;

	i = 1;
	count = 0;
	temp = stack;
	while (i < ac && temp->valid == 0)
	{
		temp = temp->next;
		i++;
	}
	while (i < ac && temp->value < mid)
	{
		count++;
		temp = temp->next;
		i++;
	}
	return (count);
}

int valid_count_b_top(t_stack *stack, int mid, int ac)
{
	int i;
	t_stack *temp;
	int count;

	i = 1;
	count = 0;
	temp = stack;
	while (i < ac && temp->valid == 0)
	{
		temp = temp->next;
		i++;
	}
	while (i < ac && temp->value >= mid)
	{
		count++;
		temp = temp->next;
		i++;
	}
	return (count);
}

void three_sort_a(t_stack *stack, int ac) // only use when you KNOW there's 3 valid remaining
{
	t_stack *temp;

	temp = stack;
	while (temp->valid == 0)
		temp = temp->next;
	if (temp->value < temp->next->value)
	{
		if (temp->next->next->value < temp->value) // 2 3 1
			rra(stack);
		else if (temp->next->value > temp->next->next->value) // 1 3 2
		{
			ra(stack, ac);
			sa(stack, ac);
			rra(stack);
		}
	}
	else if (temp->next->value > temp->next->next->value) // 3 2 1
	{
		sa(stack, ac);
		rra(stack);
	}
	else if (temp->value < temp->next->next->value) // 2 1 3
		sa(stack, ac);
	else if (temp->value > temp->next->next->value) // 3 1 2
		ra(stack, ac);
}

void duplicate_stack(t_stack *stack_c, t_stack *stack, int ac)
{
	int i;
	t_stack *temp_c;
	t_stack *temp;

	i = 1;
	temp = stack;
	temp_c = stack_c;
	temp_c->value = temp->value;
	temp_c->valid = temp->valid;
	while (i < ac - 1)
	{
		temp = temp->next;
		temp_c = temp_c->next;
		temp_c->value = temp->value;
		temp_c->valid = temp->valid;
		i++;
	}
}

int midpoint(t_stack *stack_a, int ac) // make sure count > 3
{
	int count;
	int i;
	t_stack *temp;
	t_stack *stack_c;
	int mid;

	stack_c = zero_insert_stack(ac);
	duplicate_stack(stack_c, stack_a, ac);
	unruled_insertion_sort(stack_c, ac, 1, 0);
	temp = stack_c;
	count = valid_count(stack_c, ac);
	// printf("count = %i\n", count);
	i = 0;
	while (temp->valid == 0)
		temp = temp->next;
	while (i < (count / 2))
	{
		temp = temp->next;
		i++;
	}
	mid = temp->value;
	free_stack_list(stack_c);
	return (mid);
}

int midpoint_free(t_stack *stack_new, int ac) // make sure count > 3
{
	int count;
	int i;
	t_stack *temp;
	t_stack *stack_c;
	int mid;

	stack_c = zero_insert_stack(ac);
	duplicate_stack(stack_c, stack_new, ac);
	unruled_insertion_sort(stack_c, ac, 1, 0);
	temp = stack_c;
	count = valid_count(stack_c, ac);
	// printf("count = %i\n", count);
	i = 0;
	while (temp->valid == 0)
		temp = temp->next;
	while (i < (count / 2))
	{
		temp = temp->next;
		i++;
	}
	mid = temp->value;
	free_stack_list(stack_c);
	free_stack_cycle(stack_new, ac);
	return (mid);
}

int scan_left(t_stack *stack, int mid, int ac)
{
	t_stack *temp;
	int i;

	temp = stack;
	i = 1;
	while (temp->valid == 0 && i < ac)
	{
		temp = temp->next;
		i++;
	}
	while (temp->valid == 1 && i < ac)
	{
		if (temp->value < mid)
			return (1);
		temp = temp->next;
		i++;
	}
	return (0);
}

int scan_left_b(t_stack *stack, int mid, int ac)
{
	t_stack *temp;
	int i;

	temp = stack;
	i = 1;
	while (temp->valid == 0 && i < ac)
	{
		temp = temp->next;
		i++;
	}
	while (temp->valid == 1 && i < ac)
	{
		if (temp->value >= mid)
			return (1);
		temp = temp->next;
		i++;
	}
	return (0);
}

void sort_less_than_three_a(t_stack *stack_a, int count, int ac)
{
	t_stack *temp;

	temp = stack_a;
	if (count == 0)
		return;
	while (temp->valid == 0)
		temp = temp->next;
	if (count == 1)
		return ;
	else if (count == 2)
	{
		if (temp->value > temp->next->value)
			sa(stack_a, ac);
		return ;
	}
	else if (count == 3)
		return three_sort_a(stack_a, ac);
}

void sort_less_than_three_b(t_stack *stack_b, int count, int ac)
{
	t_stack *temp;

	temp = stack_b;
	if (count == 0)
		return;
	while (temp->valid == 0)
		temp = temp->next;
	if (count == 1)
		return ;
	else if (count == 2)
	{
		if (temp->value > temp->next->value)
			sb(stack_b, ac);
		return ;
	}
	else if (count == 3)
		return three_sort_a(stack_b, ac);
}

void midpoint_algo_first(t_stack *stack_a, t_stack *stack_b, int ac, int mid)
{
	t_stack *temp;

	temp = stack_a;
	// printf("mid=%i\n", mid);
	while (scan_left(stack_a, mid, ac) && valid_count(stack_a, ac) > 3)
	{
		while (temp->valid == 0 && scan_left(stack_a, mid, ac) && valid_count(stack_a, ac) > 3)
			temp = temp->next;
		while (temp->value >= mid && scan_left(stack_a, mid, ac) && valid_count(stack_a, ac) > 3)
			ra(stack_a, ac);
		while (temp->value < mid && scan_left(stack_a, mid, ac) && valid_count(stack_a, ac) > 3)
		{
			pb(stack_a, stack_b);
			temp = temp->next;
			// printf("valid=%i\n", valid_count(stack_a, ac));
		}
		temp = temp->prev;
		while (temp->valid == 0 && scan_left(stack_a, mid, ac) && valid_count(stack_a, ac) > 3)
			temp = temp->prev;
		while (temp->value >= mid && scan_left(stack_a, mid, ac) && valid_count(stack_a, ac) > 3)
			rra(stack_a);
		while (temp->value < mid && temp->valid == 1 && valid_count(stack_a, ac) > 3)
		{
			rra(stack_a);
			pb(stack_a, stack_b);
			// printf("valid=%i\n", valid_count(stack_a, ac));
		}
		temp = temp->next;
	}
	sort_less_than_three_a(stack_a, valid_count(stack_a, ac), ac);
}

int midpoint_chunk_lessthan_a(t_stack *stack_a, int lessthan, int ac)
{
	int i;
	t_stack *temp;
	t_stack *temp_new;
	t_stack *stack_a_new; //all values = 0, valid = 0;

	i = ac;
	stack_a_new = zero_insert_stack(ac);
	set_invalid(stack_a_new, ac);
	temp = stack_a->prev;
	temp_new = stack_a_new->prev;
	while (temp->value >= lessthan && temp->valid == 1 && i > 1)
	{
		temp = temp->prev;
		i--;
	}
	while (temp->value < lessthan && temp->valid == 1 && i > 1)
	{
		temp->value = temp_new->value;
		temp_new->valid = 1;
		temp = temp->prev;
		temp_new = temp_new->prev;
		i--;
	}
	return (midpoint_free(stack_a_new, ac));
}

int midpoint_chunk_morethan_b(t_stack *stack_b, int morethan, int ac)
{
	int i;
	t_stack *temp;
	t_stack *temp_new;
	t_stack *stack_b_new; //all values = 0, valid = 0;

	i = ac;
	stack_b_new = zero_insert_stack(ac);
	set_invalid(stack_b_new, ac);
	temp = stack_b->prev;
	temp_new = stack_b_new->prev;
	while (temp->value < morethan && temp->valid == 1 && i > 1)
	{
		temp = temp->prev;
		i--;
	}
	while (temp->value >= morethan && temp->valid == 1 && i > 1)
	{
		temp->value = temp_new->value;
		temp_new->valid = 1;
		temp = temp->prev;
		temp_new = temp_new->prev;
		i--;
	}
	return (midpoint_free(stack_b_new, ac));
}

void update_stack_d(t_stack *stack_d, t_stack *stack_b, int ac, int mid)
{
	t_stack *temp;
	int previously;

	previously = stack_d->value;
	temp = stack_d->prev;
	while (temp->valid != 0)
		temp = temp->prev;
	temp->value = mid;
	temp->valid = valid_count(stack_b, ac) - previously;
	// temp->index = 
	stack_d->value = valid_count(stack_b, ac);
}

void push_b_iterate_top(t_stack *stack_a, t_stack *stack_b, int ac, int mid)
{ // sends ALL values < mid from a to b
	t_stack *temp;
	int count_ra;

	temp = stack_a;
	count_ra = 0;
	while (scan_left(stack_a, mid, ac))
	{
		while (temp->valid == 0 && scan_left(stack_a, mid, ac))
			temp = temp->next;
		while (temp->value >= mid && scan_left(stack_a, mid, ac))
		{
			ra(stack_a, ac);
			count_ra++;
		}
		while (temp->value < mid && scan_left(stack_a, mid, ac))
		{
			pb(stack_a, stack_b);
			temp = temp->next;
			// printf("valid=%i\n", valid_count(stack_a, ac));
		}
	}
	while (count_ra > 0)
	{
		rra(stack_a);
		count_ra--;
	}
}

void push_a_iterate_top(t_stack *stack_a, t_stack *stack_b, int ac, int mid)
{ // sends all values >= mid from b to a
	t_stack *temp;
	int count_rb;

	temp = stack_a;
	count_rb = 0;
	while (scan_left_b(stack_b, mid, ac))
	{
		while (temp->valid == 0 && scan_left_b(stack_b, mid, ac))
			temp = temp->next;
		while (temp->value < mid && scan_left_b(stack_b, mid, ac))
		{
			rb(stack_b, ac);
			count_rb++;
		}
		while (temp->value >= mid && scan_left_b(stack_b, mid, ac))
		{
			pa(stack_a, stack_b);
			temp = temp->next;
			// printf("valid=%i\n", valid_count(stack_a, ac));
		}
	}
	while (count_rb > 0)
	{
		rrb(stack_b);
		count_rb--;
	}
}

void midpoint_algo_two_b(t_stack *stack_a, t_stack *stack_b, t_stack *d, int ac)
{
	t_stack *temp;

	temp = stack_b;
	if (d->valid == 1)
	{
		pa(stack_a, stack_b);
	}
	else if (d->valid == 2)
	{
		while (temp->valid == 0)
			temp = temp->next;
		if (temp->value > temp->next->value)
			sb(stack_b, ac);
		pa(stack_a, stack_b);
		pa(stack_a, stack_b);
	}
	d->valid = 0;
}

void midpoint_algo_two_a(t_stack *stack_a, int mid, int ac)
{
	t_stack *temp;

	temp = stack_a;
	while (temp->valid == 0)
		temp = temp->next;
	if (valid_count_a_top(stack_a, mid, ac) == 2)
	{
		if (temp->value > temp->next->value)
			sa(stack_a, ac);
	}
}

int set_sub_zero(int sub[32][2])[32][2]
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < 32)
	{
		while (j < 2)
		{
			sub[i][j] = 0;
			j++;
		}
		i++;
	}
	return (sub);
}

int update_sub_d(int sub[32][2], t_stack *stack_b, int ac, int mid2)[32][2]
{
	int i;
	int j;
	int previously;

	previously = sub[0][1];
	i = 31;
	j = 0;
	while (sub[i][0] != 0)
		i--;
	sub[i][1] = mid;
	sub[i][0] = valid_count(stack_b, ac) - previously;
	sub[0][1] = valid_count(stack_b, ac);
}

int value_from_sub(int sub[32][2])
{
	int i;
	int j;

	i = 31;
	j = 0;
	while (sub[i][0] != 0)
		i--;
	return (sub[i][1]); 	
}

int valid_from_sub(int sub[32][2])
{
	int i;
	int j;

	i = 31;
	j = 0;
	while (sub[i][0] != 0)
		i--;
	return (sub[i][0]);
}

void midpoint_algo(t_stack *stack_a, t_stack *stack_b, t_stack *stack_d, int ac)
{
	int value;
	int valid;
	int mid;
	int mid2;
	int sub_d[32][2];

	sub_d = set_sub_zero(sub_d);
	value = value_from_sub(sub_d);
	valid = valid_from_sub(sub_d);
	if (valid == 1 || valid == 2)
	{
		midpoint_algo_two_b(stack_a, stack_b, temp, ac);
		// free_stack_cycle(sub_d, ac);
		return ;
	}
	else
	{
		t_stack *temp2 = stack_d;
		for (int k = 1; k < ac; k++)
		{
			printf("D%i [%i]: %i\n", k, temp2->valid, temp2->value);
			temp2 = temp2->next;
		}
		mid = midpoint_chunk_morethan_b(stack_b, value, ac);
		push_a_iterate_top(stack_a, stack_b, ac, mid);
		while (valid_count_a_top(stack_a, mid, ac) > 2)
		{
			mid2 = midpoint_chunk_lessthan_a(stack_a, mid, ac);
			push_b_iterate_top(stack_a, stack_b, ac, mid2);
			update_stack_d(sub_d, stack_b, ac, mid2);
		}
		midpoint_algo_two_a(stack_a, mid, ac);
		return (midpoint_algo(stack_a, stack_b, sub_d, ac));
	}
}

void sort(t_stack *stack_a, t_stack *stack_b, int ac)
{
	t_stack *stack_d_static;
	t_stack *stack_d;
	int mid;

	stack_d_static = zero_insert_stack(ac);
	set_invalid(stack_d_static, ac);
	stack_d = stack_d_static;
	if (ac <= 4)
		return (sort_less_than_three_a(stack_a, valid_count(stack_a, ac), ac));
	else if (is_sort_a(stack_a, ac)) //dealt with sizes 1-3 and already sorted lists
		return ;
	while (valid_count(stack_a, ac) > 3)
	{
		mid = midpoint(stack_a, ac);
		midpoint_algo_first(stack_a, stack_b, ac, mid);
		update_stack_d(stack_d, stack_b, ac, mid);
	}
	while (stack_d->valid == 0)
		stack_d = stack_d->next; // becomes only as long as the number of 'big chunks' in stack_b
	
	
	printf("validcount=%i\n", valid_count(stack_d, ac));
	while (valid_count(stack_d, ac) != 0)
	{
		printf("reached");
		midpoint_algo(stack_a, stack_b, stack_d, ac);
		printf("Reached");
		stack_d->valid = 0;
		stack_d = stack_d->next;
	}
	// midpoint_algo(stack_a, stack_b, ac); //(only top)

	free_stack_cycle(stack_d, ac);
}

int main(int argc, char *argv[])
{
	t_stack *stack_a;
	t_stack *stack_b;
	// t_stack *stack_c;
	

	if (!input_isvalid(argc, argv))
	{
		ft_putstr("Error\n");
		return (1);
	}
	// ft_putnbr(input_isvalid(argc, argv));
	// printf("\n%i\n\n", argc);
	stack_a = args_insert_stack(argc, argv);
	stack_b = make_stack_b(argc, argv);
	// insertion_sort(stack_a, stack_b, argc);
	sort(stack_a, stack_b, argc);


	t_stack *temp = stack_a;
	for (int k = 1; k < argc; k++)
	{
		printf("A%i [%i]: %i\n", k, temp->valid, temp->value);
		temp = temp->next;
	}
	temp = stack_b;
	for (int m = 1; m < argc; m++)
	{
		printf("B%i [%i]: %i\n", m, temp->valid, temp->value);
		temp = temp->next;
	}
	// printf("mid = %i\n", midpoint(stack_c, argc));

	free_stack_cycle(stack_a, argc);
	free_stack_cycle(stack_b, argc);
	// FREE STACK_C !!!
}