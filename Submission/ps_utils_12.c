/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utils_12.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulati <kgulati@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 16:09:16 by kgulati           #+#    #+#             */
/*   Updated: 2021/06/03 16:34:21 by kgulati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_a_rrb(t_stack *stack_b, int count_rb)
{
	while (count_rb > 0)
	{
		rrb(stack_b);
		count_rb--;
	}
}

void	push_a_top(t_stack *stack_a, t_stack *stack_b, int size, int ac)
{
	t_stack	*temp;
	int		count_rb;
	int		mid;

	temp = stack_b;
	count_rb = 0;
	mid = find_mid(stack_b, size);
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
		}
	}
	push_a_rrb(stack_b, count_rb);
}

void	twosort_b(t_stack *stack_a, t_stack *stack_b, int ac)
{
	t_stack	*temp;

	temp = stack_b;
	while (temp->valid == 0)
		temp = temp->next;
	if (temp->value < temp->next->value)
		sb(stack_b, ac);
	pa(stack_a, stack_b);
	pa(stack_a, stack_b);
}

void	twosort_a(t_stack *stack_a, int ac)
{
	t_stack	*temp;

	temp = stack_a;
	while (temp->valid == 0)
		temp = temp->next;
	if (temp->value > temp->next->value)
		sa(stack_a, ac);
}
