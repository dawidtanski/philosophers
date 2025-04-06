/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanski <dtanski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:39:09 by dtanski           #+#    #+#             */
/*   Updated: 2025/04/06 15:54:47 by dtanski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long get_time(t_time_unit unit)
{
	struct timeval	tv;
	long			res;

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
	// printf("Current time: %ld\n", res);
	return (res);
}

void	go_sleep(long	time)
{
	long	start;
	long	end;

	// end - start = time

	start = get_time(MILLISECOND);
	while (1)
	{
		if (( time > (long) 1e3) || (time > 1) || (time > (long)1e6))
			usleep((time * (long) 1e3) / 2);
		end = get_time(MILLISECOND);
		if (end >= time + start)
			return ;
	}
}

int err_exit(const char *str)
{
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}