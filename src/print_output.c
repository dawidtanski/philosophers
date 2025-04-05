/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanski <dtanski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:46:14 by dtanski           #+#    #+#             */
/*   Updated: 2025/04/04 13:02:57 by dtanski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// timestamp_in_ms X has taken a fork

void	print_output(t_status status, t_philo *philo)
{
	long	start_time;
	long	timestamp;
	int		philo_id;

	philo_id = philo->philo_id;
	start_time = philo->table->start_simulation_time;
	timestamp = get_time(MILLISECOND) - start_time;
	if (status == SLEEPING && !simulation_finished(philo->table))
	{
		printf(W "%-6ld" RST " %d is sleeping\n" RST, timestamp, philo_id);
	}
	else if (status == EATING && !simulation_finished(philo->table))
	{
		printf(W "%-6ld" RST " %d is eating\n" RST, timestamp, philo_id);
	}
	else if (status == THINKING && !simulation_finished(philo->table))
	{
		printf(W "%-6ld" RST " %d is thinking\n" RST, timestamp, philo_id);
	}
	else if (status == DIED && simulation_finished(philo->table))
	{
		printf(R "%-6ld" " Philo %d died\n" RST, timestamp, philo_id);
	}
	else if (status == GRAB_1ST_FORK || status == GRAB_2ND_FORK)
	{
		printf(W "%-6ld" RST " %d has taken a fork\n" RST, timestamp, philo_id);
	}
	else
	{
		err_exit("Printing output failed.");
	}
}