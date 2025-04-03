/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanski <dtanski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:39:09 by dtanski           #+#    #+#             */
/*   Updated: 2025/04/03 12:24:38 by dtanski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long get_time(t_time_unit unit)
{
	struct timeval	tv;
	long			res;

    gettimeofday(&tv, NULL);
	if (unit == SECOND)
		res = tv.tv_sec + tv.tv_usec * 1e-6;
	else if (unit == MILLISECOND)
		res = tv.tv_sec * 1e3 + tv.tv_usec * 1e-3;
	else if (unit == MICROSECOND)
		res = tv.tv_sec * 1e6 + tv.tv_usec;
	return (res);
}

void	go_sleep(long	time, t_time_unit	unit)
{
	long	start;
	long	end;

	// end - start = time

	start = get_time(unit);
	while (1)
	{
		if ((unit == MILLISECOND && time > 1e3)
		|| (unit == SECOND && time > 1) ||
		(unit == MICROSECOND && time > 1e6))
			usleep(time / 2);
		end = get_time(unit);
		if (end >= time + start)
			return ;
	}
}

int err_exit(const char *str)
{
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}