/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utils_10.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulati <kgulati@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:52:22 by kgulati           #+#    #+#             */
/*   Updated: 2021/06/03 15:56:14 by kgulati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	three_sort_a(t_stack *stack, int ac)
{
	t_stack	*temp;

	temp = stack;
	while (temp->valid == 0)
		temp = temp->next;
	if (temp->value < temp->next->value)
	{
		if (temp->next->next->value < temp->value)
			rra(stack);
		else if (temp->next->value > temp->next->next->value)
		{
			ra(stack, ac);
			sa(stack, ac);
			rra(stack);
		}
	}
	else if (temp->next->value > temp->next->next->value)
	{
		sa(stack, ac);
		rra(stack);
	}
	else if (temp->value < temp->next->next->value)
		sa(stack, ac);
	else if (temp->value > temp->next->next->value)
		ra(stack, ac);
}

int	scan_left(t_stack *stack, int mid, int ac)
{
	t_stack	*temp;
	int		i;

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

int	scan_left_b(t_stack *stack, int mid, int ac)
{
	t_stack	*temp;
	int		i;

	temp = stack;
	i = 1;
	while (temp->valid == 0 && i < ac)
	{
		temp = temp->next;
		i++;
	}
	while (temp->valid != 0 && i < ac)
	{
		if (temp->value >= mid)
			return (1);
		temp = temp->next;
		i++;
	}
	return (0);
}

void	sort_less_than_three_a(t_stack *stack_a, int ac)
{
	t_stack	*temp;

	temp = stack_a;
	if (ac == 2)
		return ;
	else if (ac == 3)
	{
		if (temp->value > temp->next->value)
			sa(stack_a, ac);
		return ;
	}
	else if (ac == 4)
		return (three_sort_a(stack_a, ac));
}
