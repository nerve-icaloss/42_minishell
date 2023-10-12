/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:59:30 by nserve            #+#    #+#             */
/*   Updated: 2023/10/06 12:59:32 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_UTILS_H
# define SCANNER_UTILS_H

# include "../headers/minishell.h"

int	scan_quote(t_source *src, char nc);
int scan_verticalbar(t_source *src, char nc);
int scan_ampersand(t_source *src, char nc);
int scan_lessthan(t_source *src, char nc);
int scan_morethan(t_source *src, char nc);
int	scan_bracket(t_source *src, char nc);

#endif
