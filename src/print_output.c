/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanski <dtanski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:46:14 by dtanski           #+#    #+#             */
/*   Updated: 2025/04/09 12:16:33 by dtanski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_output(t_status status, t_philo *philo)
{
	long	start_time;
	long	timestamp;
	int		philo_id;
	bool	sim_end;

	sim_end = get_bool(&philo->table->table_mtx, &philo->table->sim_end);
	philo_id = philo->philo_id;
	start_time = get_long(&philo->table->table_mtx, &philo->table->start_t);
	timestamp = get_time(MILLISECOND) - start_time;
	safe_mutex_handle(&philo->table->write_mtx, LOCK);
	if (status == SLEEPING && !sim_end)
		printf(W "%-6ld" RST " %d is sleeping\n" RST, timestamp, philo_id);
	else if (status == EATING && !sim_end)
		printf(W "%-6ld" RST " %d is eating\n" RST, timestamp, philo_id);
	else if (status == THINKING && !sim_end)
		printf(W "%-6ld" RST " %d is thinking\n" RST, timestamp, philo_id);
	else if (status == DIED
		&& get_bool(&philo->table->table_mtx, &philo->table->all_threads_ready)
		&&!get_bool(&philo->table->table_mtx, &philo->table->sim_end))
		printf(R "%-6ld" " %d died\n" RST, timestamp, philo_id);
	else if ((status == GRAB_1ST_FORK || status == GRAB_2ND_FORK)
		&& !get_bool(&philo->table->table_mtx, &philo->table->sim_end))
		printf(W "%-6ld" RST " %d has taken a fork\n" RST, timestamp, philo_id);
	safe_mutex_handle(&philo->table->write_mtx, UNLOCK);
}
