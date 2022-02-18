/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utils_5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulati <kgulati@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:45:05 by kgulati           #+#    #+#             */
/*   Updated: 2021/06/03 15:46:43 by kgulati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	s(t_stack *stack, int argc)
{
	t_stack	*temp;
	int		store;

	temp = stack;
	while (temp->valid == 0 && temp->index != argc - 2)
		temp = temp->next;
	if (temp->index != argc - 1)
	{
		store = temp->value;
		temp->value = temp->next->value;
		temp->next->value = store;
	}
}

void	sa(t_stack *stack_a, int argc)
{
	s(stack_a, argc);
	ft_putstr("sa\n");
}

void	sb(t_stack *stack_b, int argc)
{
	s(stack_b, argc);
	ft_putstr("sb\n");
}

void	ss(t_stack *stack_a, t_stack *stack_b, int argc)
{
	s(stack_a, argc);
	s(stack_b, argc);
	ft_putstr("ss\n");
}
