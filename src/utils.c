/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanski <dtanski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:39:09 by dtanski           #+#    #+#             */
/*   Updated: 2025/04/13 21:26:44 by dtanski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	get_time(t_time_unit unit)
{
	struct timeval	tv;
	long			res;

	res = 0;
	if (gettimeofday(&tv, NULL) != 0)
		err_exit("Gettimeoftheday failure");
	if (unit == SECOND)
		res = tv.tv_sec + tv.tv_usec * (long)1e-6;
	else if (unit == MILLISECOND)
		res = tv.tv_sec * (long)1e3 + tv.tv_usec / 1000;
	else if (unit == MICROSECOND)
		res = tv.tv_sec * (long)1e6 + tv.tv_usec;
	else
		err_exit("Bad time unit");
	return (res);
}

void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = get_time(MICROSECOND);
	while (get_time(MICROSECOND) - start < usec)
	{
		if (get_bool(&table->table_mtx, &table->sim_end))
			break ;
		elapsed = get_time(MICROSECOND) - start;
		remaining = usec - elapsed;
		if (remaining > 1e3)
			usleep(remaining / 2);
		else
		{
			while (get_time(MICROSECOND) - start < usec)
				;
		}
	}
}

int	err_exit(const char *str)
{
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}
