/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanski <dtanski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:49:39 by dtanski           #+#    #+#             */
/*   Updated: 2025/04/09 12:29:23 by dtanski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*safe_malloc(size_t	size)
{
	void	*ret;

	ret = malloc(size);
	if (ret == NULL)
		err_exit("Mallocing failed");
	return (ret);
}

static void	handle_mutex_error(int status, t_opcode opcode)
{
	if (0 == status)
		return ;
	if (EINVAL == status && (LOCK == opcode || UNLOCK == opcode))
		err_exit("The value specified by mutex is invalid.");
	else if (EINVAL == status && INIT == opcode)
		err_exit("The value specified by attr is invalid");
	else if (EDEADLK == status)
		err_exit("A deadlock would occur if the thread"
			"blocked waiting for mutex");
	else if (EPERM == status)
		err_exit("The current thread does not hold a lock on mutex");
	else if (ENOMEM == status)
		err_exit("The process cannot allocate enough"
			"memory to create another mutex.");
	else if (EBUSY == status)
		err_exit("Mutex is locked");
}

void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (opcode == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		err_exit("Wrong opcode for mutex handle!");
}

static void	handle_thread_error(int status, t_opcode opcode)
{
	if (0 == status)
		return ;
	if (EAGAIN == status)
		err_exit("No resources to create another thread");
	else if (EPERM == status)
		err_exit("The caller don/'t have appropriate permission\n");
	else if (EINVAL == status && CREATE == opcode)
		err_exit("The value specified by attr is invalid.");
	else if (EINVAL == status && (JOIN == opcode || DETACH == opcode))
		err_exit("The value specified by thread is not joinable.\n");
	else if (ESRCH == status)
		err_exit("No thread could be found corresponding to that"
			"specified by the given thread ID, thread.");
	else if (EDEADLK == status)
		err_exit("A deadlock was detected or the value of"
			"thread specifies the calling thread");
}

void	thread_handle(pthread_t *t, void *(*f)(void *), void *d, t_opcode o)
{
	if (o == CREATE)
		handle_thread_error(pthread_create(t, NULL, f, d), o);
	else if (o == JOIN)
		handle_thread_error(pthread_join(*t, NULL), o);
	else if (o == DETACH)
		handle_thread_error(pthread_detach(*t), o);
	else
		err_exit("Wrong opcode for thread handle");
}
