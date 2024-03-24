/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:29:21 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/24 15:31:41 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	*print_msg_helper(t_philo *ph, long usec, int flag)
{
	char	*msec_str;
	char	*name_str;
	char	*ret;
	char	*tmp;

	usec = usec / THOUSAND;
	msec_str = ft_itoa((int)usec);
	name_str = ft_itoa((int)ph->info->name);
	ret = ft_strjoin(msec_str, " ");
	tmp = ft_strjoin(ret, name_str);
	free(msec_str);
	free(name_str);
	free(ret);
	if (flag == SLEEP)
		ret = ft_strjoin(tmp, SLEEP_MSG);
	else if (flag == EAT)
		ret = ft_strjoin(tmp, EAT_MSG);
	else if (flag == THINK)
		ret = ft_strjoin(tmp, THINK_MSG);
	else if (flag == TAKE)
		ret = ft_strjoin(tmp, TAKE_MSG);
	else if (flag == UNTAKE)
		ret = ft_strjoin(tmp, UNTAKE_MSG);
	else if (flag == DIED)
		ret = ft_strjoin(tmp, DIE_MSG);
	free(tmp);
	return (ret);
}

void	print_msg(t_philo *ph, long usec, int flag)
{
	char	*msg;
	int		len;

	msg = print_msg_helper(ph, usec, flag);
	len = ft_strlen(msg);
	sem_wait(ph->sem->print);
	write(1, msg, len);
	if (flag == DIED)
		exit(FUN_FAIL);
	sem_post(ph->sem->print);
}

void	*th_eating(void *in)
{
	t_philo	*ph;

	ph = (t_philo *)in;
	sem_wait(ph->sem->fork);
	print_msg(ph, ft_usec_now() - ph->info->start_time, TAKE);
	sem_wait(ph->sem->fork);
	print_msg(ph, ft_usec_now() - ph->info->start_time, TAKE);
	*(ph->flag) = EAT;
	if (ph->info->num_must_eat != -1)
		sem_wait(ph->sem->count);
	return (NULL);
}
