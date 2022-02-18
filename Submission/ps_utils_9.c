/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utils_9.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulati <kgulati@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:49:02 by kgulati           #+#    #+#             */
/*   Updated: 2021/06/03 18:27:59 by kgulati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_repetition(int ac, char *av[])
{
	int	i;
	int	j;
	int	num;

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

int	input_isvalid(int ac, char *av[])
{
	int	arg;

	arg = 1;
	if (ac < 1)
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

int	is_sort_a(t_stack *stack, int ac)
{
	int		i;
	t_stack	*temp;

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

void	sub_unruled_ins_sort(t_stack *temp, int min)
{
	t_stack	*temp2;

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

void	unruled_insertion_sort(t_stack *stack, int ac, int i, int min)
{
	t_stack	*temp;

	temp = stack;
	temp->prev = NULL;
	while (i++ < ac - 1)
		temp = temp->next;
	temp->next = NULL;
	temp = stack;
	sub_unruled_ins_sort(temp, min);
}
