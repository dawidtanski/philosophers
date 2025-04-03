/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanski <dtanski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:49:39 by dtanski           #+#    #+#             */
/*   Updated: 2025/04/02 21:02:56 by dtanski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*safe_malloc(size_t	size)
{
	void	*ret;

	ret = malloc(size);
	if (ret = NULL)
		err_exit("Mallocing failed");
	return (ret);
}

static void	handle_mutex_error(int status, t_opcode opcode)
{
	if (0 == status)
		return;
	if (EINVAL == status && (LOCK == opcode || UNLOCK == opcode))
		exit_error("The value specified by mutex is invalid.");
	else if (EINVAL == status && INIT == opcode)
		exit_error("The value specified by attr is invalid");
	else if (EDEADLK == status)
		exit_error("A deadlock would occur if the thread blocked waiting for mutex");
	else if (EPERM == status)
		exit_error("The current thread does not hold a lock on mutex");
	else if (ENOMEM == status)
		exit_error("The process cannot allocate enough memory to create another mutex.");
	else if (EBUSY == status)
		exit_error("Mutex is locked");
}

void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		handle_mutex_error(pthread_mutex_init(mutex), opcode);
	else if (opcode == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		err_exit("Wrong opcode for mutex handle!");
}

static void handle_thread_error(int status, t_opcode opcode)
	{
		if (0 == status)
			return;
		if (EAGAIN == status)
			exit_error("No resources to create another thread");
		else if (EPERM == status)
			exit_error("The caller don/'t have appropriate permission\n");
		else if (EINVAL == status && CREATE == opcode)
			exit_error("The value specified by attr is invalid.");
		else if (EINVAL == status && (JOIN == opcode || DETACH == opcode))
			exit_error("The value specified by thread is not joinable.\n");
		else if (ESRCH == status)
			exit_error("No thread could be found corresponding to that"
				"specified by the given thread ID, thread.");
		else if (EDEADLK == status)
			exit_error("A deadlock was detected or the value of"
			"thread specifies the calling thread");
	}

	void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode)
	{
		if (opcode == CREATE)
			handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
		else if (opcode == JOIN)
			handle_thread_error(pthread_join(*thread, NULL), opcode);
		else if (opcode == DETACH)
			handle_thread_error(pthread_detach(*thread), opcode);
		else
			err_exit("Wrong opcode for thread handle");
	}