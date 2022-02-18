/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulati <kgulati@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 16:20:57 by kgulati           #+#    #+#             */
/*   Updated: 2021/06/03 18:28:49 by kgulati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	quick_sort_b(t_stack *stack_a, t_stack *stack_b, int size, int ac)
{
	if (size == 1)
		pa(stack_a, stack_b);
	else if (size == 2)
		twosort_b(stack_a, stack_b, ac);
	else
	{
		push_a_top(stack_a, stack_b, size, ac);
		quick_sort_a(stack_a, stack_b, (size - (size / 2)), ac);
		quick_sort_b(stack_a, stack_b, (size / 2), ac);
	}
}

void	quick_sort_a(t_stack *stack_a, t_stack *stack_b, int size, int ac)
{
	if (size == 1)
		return ;
	else if (size == 2)
		twosort_a(stack_a, ac);
	else
	{
		push_b_top(stack_a, stack_b, size, ac);
		quick_sort_a(stack_a, stack_b, (size - (size / 2)), ac);
		quick_sort_b(stack_a, stack_b, (size / 2), ac);
	}
}

void	sort_less_than_five_a(t_stack *stack_a, t_stack *stack_b, int ac)
{
	if (ac == 5)
	{
		push_b_top_base(stack_a, stack_b, 4, 5);
		twosort_a(stack_a, ac);
		twosort_b(stack_a, stack_b, ac);
	}
	else if (ac == 6)
	{
		push_b_top_base(stack_a, stack_b, 5, 6);
		three_sort_a(stack_a, ac);
		twosort_b(stack_a, stack_b, ac);
	}
}

int	main(int argc, char *argv[])
{
	t_stack	*stack_a;
	t_stack	*stack_b;

	if (!input_isvalid(argc, argv))
	{
		ft_putstr("Error\n");
		return (1);
	}
	if (argc == 1)
		return (0);
	stack_a = args_insert_stack(argc, argv);
	stack_b = make_stack_b(argc, argv);
	if (!is_sort_a(stack_a, argc))
	{
		if (argc <= 4)
			sort_less_than_three_a(stack_a, argc);
		else if (argc <= 6)
			sort_less_than_five_a(stack_a, stack_b, argc);
		else
			quick_sort_a(stack_a, stack_b, argc - 1, argc);
	}
	free_stack_cycle(stack_a, argc);
	free_stack_cycle(stack_b, argc);
}
