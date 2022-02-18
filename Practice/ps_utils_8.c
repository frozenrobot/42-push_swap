/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utils_8.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulati <kgulati@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:47:30 by kgulati           #+#    #+#             */
/*   Updated: 2021/06/03 16:50:39 by kgulati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rr(t_stack *stack_a, t_stack *stack_b, int argc)
{
	r(stack_a, argc);
	r(stack_b, argc);
	ft_putstr("rr\n");
}

void	rrab(t_stack *stack)
{
	t_stack	*temp;
	int		store;

	temp = stack->prev;
	store = temp->value;
	while (temp->index != 1 && temp->prev->valid != 0)
	{
		temp->value = temp->prev->value;
		temp = temp->prev;
	}
	temp->value = store;
}

void	rra(t_stack *stack_a)
{
	rrab(stack_a);
	ft_putstr("rra\n");
}

void	rrb(t_stack *stack_b)
{
	rrab(stack_b);
	ft_putstr("rrb\n");
}

void	rrr(t_stack *stack_a, t_stack *stack_b)
{
	rrab(stack_a);
	rrab(stack_b);
	ft_putstr("rrr\n");
}
