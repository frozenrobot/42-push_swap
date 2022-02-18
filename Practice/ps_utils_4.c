/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utils_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulati <kgulati@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:44:01 by kgulati           #+#    #+#             */
/*   Updated: 2021/06/03 15:44:45 by kgulati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*args_insert_stack(int ac, char *av[])
{
	int		i;
	t_stack	*stack;
	t_stack	*temp;

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

t_stack	*zero_insert_stack(int ac)
{
	int		i;
	t_stack	*stack;
	t_stack	*temp;

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

void	set_invalid(t_stack *stack, int ac)
{
	int		i;
	t_stack	*temp;

	i = 1;
	temp = stack;
	while (i < ac)
	{
		temp->valid = 0;
		temp = temp->next;
		i++;
	}
}

t_stack	*make_stack_b(int ac, char *av[])
{
	t_stack	*stack;
	t_stack	*temp;
	int		i;

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
