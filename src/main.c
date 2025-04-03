/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanski <dtanski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:44:48 by dtanski           #+#    #+#             */
/*   Updated: 2025/04/03 20:43:28 by dtanski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*
timestamp_in_ms X has taken a fork

./philo 5 800 200 200 7

5 — The number of philosophers
800 — The time a philosopher will die if he doesn’t eat
200 — The time it takes a philosopher to eat
200 — The time it takes a philosopher to sleep
7 — Number of times all the philosophers need to eat before terminating the program **
*/

int main(int argc, char *argv[])
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		parse_input(&table, argv);
		data_init(&table);
		simulation(&table); // TODO
		clean(&table); // TODO
	}
	else
	{
		err_exit(R "Error!" RST "Wrong number of arguments!\n"
			"Philo takes 4 or 5 args :" G "./philo 5 700 200 200 [7]" RST);
	}
	return (0);
}

