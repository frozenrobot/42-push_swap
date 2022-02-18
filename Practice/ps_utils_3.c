/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utils_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulati <kgulati@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:43:27 by kgulati           #+#    #+#             */
/*   Updated: 2021/06/03 16:36:35 by kgulati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	valid_arg(char *str)
{
	int		i;
	long	int_min;
	long	int_max;
	long	num;

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
	if (num > int_max || num < int_min)
		return (0);
	return (1);
}

void	free_stack_list(t_stack *stack)
{
	t_stack	*temp;

	temp = stack;
	while (temp->next->next)
		temp = temp->next;
	stack = temp->next;
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

void	free_stack_cycle(t_stack *stack, int argc)
{
	t_stack	*temp;

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

t_stack	*create_stack_elem(int num, int i)
{
	t_stack	*elem;

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

t_stack	*stack_add_back(t_stack *stack, int num, int i)
{
	t_stack	*temp;
	t_stack	*new;

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
