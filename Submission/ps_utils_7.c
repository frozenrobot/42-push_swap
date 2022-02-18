/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utils_7.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulati <kgulati@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:47:04 by kgulati           #+#    #+#             */
/*   Updated: 2021/06/03 15:47:26 by kgulati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pb(t_stack *stack_a, t_stack *stack_b)
{
	t_stack	*temp;
	int		store;

	temp = stack_a;
	while (temp->valid == 0)
		temp = temp->next;
	store = temp->value;
	temp->valid = 0;
	temp = stack_b->prev;
	while (temp->valid == 1)
		temp = temp->prev;
	temp->valid = 1;
	temp->value = store;
	ft_putstr("pb\n");
}

void	pa(t_stack *stack_a, t_stack *stack_b)
{
	t_stack	*temp;
	int		store;

	temp = stack_b;
	while (temp->valid == 0)
		temp = temp->next;
	store = temp->value;
	temp->valid = 0;
	temp = stack_a->prev;
	while (temp->valid == 1)
		temp = temp->prev;
	temp->valid = 1;
	temp->value = store;
	ft_putstr("pa\n");
}

void	r(t_stack *stack, int argc)
{
	t_stack	*temp;
	int		store;

	temp = stack;
	while (temp->valid == 0)
		temp = temp->next;
	store = temp->value;
	while (temp->index != argc - 1)
	{
		temp->value = temp->next->value;
		temp = temp->next;
	}
	temp->value = store;
}

void	ra(t_stack *stack_a, int argc)
{
	r(stack_a, argc);
	ft_putstr("ra\n");
}

void	rb(t_stack *stack_b, int argc)
{
	r(stack_b, argc);
	ft_putstr("rb\n");
}
