/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulati <kgulati@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:11:15 by kgulati           #+#    #+#             */
/*   Updated: 2021/06/03 16:32:29 by kgulati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_stack
{
	int				value;
	struct s_stack	*next;
	struct s_stack	*prev;
	int				index;
	int				valid;
}				t_stack;

void	ft_putchar(char c);
void	ft_putstr(char *s);
int		ft_strlen(char *str);
int		check_negative(int nb);
void	ft_putnbr(int nb);
int		ft_isspace(char c);
int		check_size_ahead(char *str, int i);
long	ten_power(int exp);
long	convert_to_int(char *str, int i, int size);
long	ft_atoi(char *str);
int		valid_arg(char *str);
void	free_stack_list(t_stack *stack);
void	free_stack_cycle(t_stack *stack, int argc);
t_stack	*create_stack_elem(int num, int i);
t_stack	*stack_add_back(t_stack *stack, int num, int i);
t_stack	*args_insert_stack(int ac, char *av[]);
t_stack	*zero_insert_stack(int ac);
void	set_invalid(t_stack *stack, int ac);
t_stack	*make_stack_b(int ac, char *av[]);
void	s(t_stack *stack, int argc);
void	sa(t_stack *stack_a, int argc);
void	sb(t_stack *stack_b, int argc);
void	ss(t_stack *stack_a, t_stack *stack_b, int argc);
void	pb(t_stack *stack_a, t_stack *stack_b);
void	pa(t_stack *stack_a, t_stack *stack_b);
void	r(t_stack *stack, int argc);
void	ra(t_stack *stack_a, int argc);
void	rb(t_stack *stack_b, int argc);
void	rr(t_stack *stack_a, t_stack *stack_b, int argc);
void	rrab(t_stack *stack);
void	rra(t_stack *stack_a);
void	rrb(t_stack *stack_b);
void	rrr(t_stack *stack_a, t_stack *stack_b);
int		check_repetition(int ac, char *av[]);
int		input_isvalid(int ac, char *av[]);
int		is_sort_a(t_stack *stack, int ac);
void	sub_unruled_ins_sort(t_stack *temp, int min);
void	unruled_insertion_sort(t_stack *stack, int ac, int i, int min);
void	three_sort_a(t_stack *stack, int ac);
int		scan_left(t_stack *stack, int mid, int ac);
int		scan_left_b(t_stack *stack, int mid, int ac);
void	sort_less_than_three_a(t_stack *stack_a, int ac);
int		sub_findmid(t_stack *new, t_stack *temp_new, int sze);
int		find_mid(t_stack *stack, int size);
void	push_b_rra(t_stack *stack_a, int count);
void	push_b_top(t_stack *stack_a, t_stack *stack_b, int size, int ac);
void	push_b_top_base(t_stack *stack_a, t_stack *stack_b, int size, int ac);
void	push_a_top(t_stack *stack_a, t_stack *stack_b, int size, int ac);
void	twosort_b(t_stack *stack_a, t_stack *stack_b, int ac);
void	twosort_a(t_stack *stack_a, int ac);
void	quick_sort_b(t_stack *stack_a, t_stack *stack_b, int size, int ac);
void	quick_sort_a(t_stack *stack_a, t_stack *stack_b, int size, int ac);
void	sort_less_than_five_a(t_stack *stack_a, t_stack *stack_b, int ac);

#endif
