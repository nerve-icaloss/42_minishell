/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:26:48 by nserve            #+#    #+#             */
/*   Updated: 2023/10/05 15:26:51 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H

# include "minishell.h"

int	scan_quote(t_source *src);
int	scan_verticalbar(t_source *src, char nc);
int	scan_ampersand(t_source *src, char nc);
int	scan_lessthan(t_source *src, char nc);
int	scan_morethan(t_source *src, char nc);
int	scan_space(t_source *src);
int	scan_bracket(t_source *src, char nc);

t_token	*tokenize(t_source *src);

#endif
