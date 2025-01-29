/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdPING.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:57:30 by akurochk          #+#    #+#             */
/*   Updated: 2025/01/29 17:59:14 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::cmdPing(std::vector<std::string> tokens, int fd) {
	Client *c = getClientByFd(fd);
	(tokens.size() > 1) ? c->setReplyBuffer("PONG " + tokens[1]) : c->setReplyBuffer("PONG");
}

