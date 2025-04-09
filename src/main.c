/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanski <dtanski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:44:48 by dtanski           #+#    #+#             */
/*   Updated: 2025/04/09 12:29:55 by dtanski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		parse_input(&table, argv);
		data_init(&table);
		simulation(&table);
		clean(&table);
	}
	else
	{
		err_exit(R "Error!" RST "Wrong number of arguments!\n"
			"Philo takes 4 or 5 args :" G "./philo 5 700 200 200 [7]" RST);
	}
	return (0);
}
