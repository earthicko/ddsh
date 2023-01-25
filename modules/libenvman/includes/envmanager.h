/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envmanager.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:42:25 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:42:29 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVMANAGER_H
# define ENVMANAGER_H

int		envman_init(char **envp);
int		envman_clear(void);
int		envman_getval(char *name, char **buf);
int		envman_setval(char *name, char *val, int exp);
int		envman_unsetval(char *name);
int		envman_getenvp(char ***buf);
int		envman_printlist_export(void);
int		envman_printlist_declare(void);

int		envman_split_envstr(char *str, char **ret_name, char **ret_val);
int		exit_stat_manager(int new_stat);

#endif
