/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanski <dtanski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:38:57 by dtanski           #+#    #+#             */
/*   Updated: 2025/04/05 11:31:18 by dtanski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static bool is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (true);
	else
		return (false);
}

static bool is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (true);
	else
		return (false);
}

static long input_checker(char *str)
{
	long		number;
	size_t			len;

	len = 0;
	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	if (*str == '-')
		err_exit("This program doesn't take negative numbers as input!");
	while (str[len])
		len++;
	number = 0;
	while (*str)
	{
		if (is_digit(*str))
		{
			number *= 10;
			number += *str - 48;
			str++;
		}
	}
	if (number > INT_MAX)
		err_exit("Value too big. Maximum value == INT_MAX ");
	return (number);
}

//  ./philo 5 800 200 200 7

void	parse_input(t_table *table, char *argv[])
{
	table->num_of_philos = input_checker(argv[1]);
	table->time_to_die = input_checker(argv[2]);
	table->time_to_eat = input_checker(argv[3]);
	table->time_to_sleep = input_checker(argv[4]);
	if (argv[5])
		table->meals_limit = input_checker(argv[5]);
	else
		table->meals_limit = -1;
}

