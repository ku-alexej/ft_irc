/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdCAP.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:57:22 by akurochk          #+#    #+#             */
/*   Updated: 2025/02/10 14:00:49 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::cmdCap(std::vector<std::string> tokens, int fd) {
	Client *c = getClientByFd(fd);

	if (tokens.size() < 2) {
		return ;
	}

	if (tokens[1] == "LS") {
		c->setCapOn(true);
		c->setReplyBuffer("CAP * LS :");
		return ;
	}

	if (tokens[1] == "END") {
		c->setCapOn(false);
		if (c->getPassOk() && c->getNickname() != "" && c->getUsername() != "") {
				c->setRegistred(true);
				c->setReplyBuffer(RPL_WELCOME(c->getNickname(), c->getNickname(), c->getUsername(), c->getHostname()));
		}
	}
}
