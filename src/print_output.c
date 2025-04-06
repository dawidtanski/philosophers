/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanski <dtanski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:46:14 by dtanski           #+#    #+#             */
/*   Updated: 2025/04/06 16:25:48 by dtanski          ###   ########.fr       */
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
	start_time = get_long(&philo->table->table_mtx, &philo->table->start_simulation_time);
	timestamp = get_time(MILLISECOND) - start_time;
	// printf(Y "\n %ld \n",start_time);
	// printf(Y "\n %ld \n",timestamp);
	safe_mutex_handle(&philo->table->write_mtx, LOCK);
	if (status == SLEEPING && !get_bool(&philo->table->table_mtx, &philo->table->simulation_finished))
	{
		printf(W "%-6ld" RST " %d is sleeping\n" RST, timestamp, philo_id);
	}
	else if (status == EATING && !get_bool(&philo->table->table_mtx, &philo->table->simulation_finished))
	{
		printf(W "%-6ld" RST " %d is eating\n" RST, timestamp, philo_id);
	}
	else if (status == THINKING && !get_bool(&philo->table->table_mtx, &philo->table->simulation_finished))
	{
		printf(W "%-6ld" RST " %d is thinking\n" RST, timestamp, philo_id);
	}
	else if (status == DIED && get_bool(&philo->table->table_mtx, &philo->table->all_threads_ready) &&!get_bool(&philo->table->table_mtx, &philo->table->simulation_finished))
	{
		printf(R "%-6ld" " Philo %d died\n" RST, timestamp, philo_id);
	}
	else if (status == GRAB_1ST_FORK || status == GRAB_2ND_FORK)
	{
		printf(W "%-6ld" RST " %d has taken a fork\n" RST, timestamp, philo_id);
	}
	else
		err_exit("Printing output failed.");
	safe_mutex_handle(&philo->table->write_mtx, UNLOCK);
}