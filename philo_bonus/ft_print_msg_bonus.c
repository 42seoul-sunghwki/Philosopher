/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_msg_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 16:10:52 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/24 19:23:21 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static char	*print_join_helper(long name, long usec)
{
	char	*msec_str;
	char	*name_str;
	char	*tmp;
	char	*ret;

	usec = usec / THOUSAND;
	msec_str = ft_itoa((int)usec);
	name_str = ft_itoa((int)name);
	tmp = ft_strjoin(msec_str, " ");
	ret = ft_strjoin(tmp, name_str);
	free(msec_str);
	free(name_str);
	free(tmp);
	return (ret);
}

static char	*print_msg_helper(t_philo *ph, long usec, int flag)
{
	char	*ret;
	char	*tmp;

	tmp = print_join_helper(ph->info->name, usec);
	ret = NULL;
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
	char	*tmp;
	int		len;

	msg = print_msg_helper(ph, usec, flag);
	len = ft_strlen(msg);
	sem_wait(ph->sem->print);
	write(1, msg, len);
	if (flag == DIED)
	{
		sem_close(ph->flag_sem);
		tmp = sem_flag_name(ph);
		sem_unlink(tmp);
		free(tmp);
		exit (FUN_FAIL);
	}
	sem_post(ph->sem->print);
	free(msg);
}
