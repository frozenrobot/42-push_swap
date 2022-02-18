/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utils_11.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulati <kgulati@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:56:43 by kgulati           #+#    #+#             */
/*   Updated: 2021/06/03 17:05:55 by kgulati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	sub_findmid(t_stack *new, t_stack *temp_new, int sze)
{
	int	i;
	int	mid;

	i = 0;
	while (i < (sze / 2))
	{
		temp_new = temp_new->next;
		i++;
	}
	mid = temp_new->value;
	free_stack_list(new);
	return (mid);
}

int	find_mid(t_stack *stack, int size)
{
	int		i;
	t_stack	*temp;
	t_stack	*stack_new;
	t_stack	*temp_new;

	i = 0;
	temp = stack;
	stack_new = zero_insert_stack(size + 1);
	temp_new = stack_new;
	while (temp->valid == 0)
		temp = temp->next;
	while (i < size)
	{
		temp_new->value = temp->value;
		temp = temp->next;
		temp_new = temp_new->next;
		i++;
	}
	unruled_insertion_sort(stack_new, size + 1, 1, 0);
	return (sub_findmid(stack_new, temp_new, size));
}

void	push_b_rra(t_stack *stack_a, int count_ra)
{
	while (count_ra > 0)
	{
		rra(stack_a);
		count_ra--;
	}
}

void	push_b_top(t_stack *stack_a, t_stack *stack_b, int size, int ac)
{
	t_stack	*temp;
	int		count_ra;
	int		mid;

	temp = stack_a;
	count_ra = 0;
	mid = find_mid(stack_a, size);
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
		}
	}
	push_b_rra(stack_a, count_ra);
}

void	push_b_top_base(t_stack *stack_a, t_stack *stack_b, int size, int ac)
{
	t_stack	*temp;
	int		mid;

	temp = stack_a;
	mid = find_mid(stack_a, size);
	while (scan_left(stack_a, mid, ac))
	{
		while (temp->valid == 0 && scan_left(stack_a, mid, ac))
			temp = temp->next;
		while (temp->value >= mid && scan_left(stack_a, mid, ac))
		{
			ra(stack_a, ac);
		}
		while (temp->value < mid && scan_left(stack_a, mid, ac))
		{
			pb(stack_a, stack_b);
			temp = temp->next;
		}
	}
}
