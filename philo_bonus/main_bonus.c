/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 22:04:32 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/21 15:01:09 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	start_simulation(t_info *info, t_sem *sem)
{
	int	*pid;
	int	num;

	pid = (int *)malloc(sizeof(int) * info->philo_num);
	if (!pid)
		return ;
	num = 0;
	while (num < info->philo_num)
	{
		info->name = num + 1;
		pid[num] = fork();
		if (pid[num] == 0)
		{
			philo(info, sem);
			exit (FUN_SUC);
		}
		usleep(1000);
		num++;
	}
	if (waitpid(-1, NULL, 0))
	{
		printf("kill all\n");
		while (--(info->philo_num))
		{
			kill(pid[info->philo_num], SIGKILL);
		}
		free(pid);
	}
}

void	print_init(t_info *info)
{
	printf("philo_num: %ld\n", info->philo_num);
	printf("time_to_die: %ld\n", info->time_to_die);
	printf("time_to_eat: %ld\n", info->time_to_eat);
	printf("time_to_sleep: %ld\n", info->time_to_sleep);
	printf("must_eat: %ld\n", info->num_must_eat);
}

int	main(int argc, char *argv[])
{
	t_info	info;
	t_sem	*sem;

	if (ft_init_info(&info, argc, argv) == FUN_FAIL)
		return (FUN_FAIL);
	print_init(&info);
	sem = ft_init_sem(&info);
	if (sem == NULL)
		return (FUN_FAIL);
	start_simulation(&info, sem);
	ft_unlink_sem(&sem);
	return (0);
}
