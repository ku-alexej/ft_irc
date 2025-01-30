/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdCAP.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:57:22 by akurochk          #+#    #+#             */
/*   Updated: 2025/01/30 15:54:06 by akurochk         ###   ########.fr       */
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
		if (c->getPassOk() && c->getNickname() != "" && c->getUsername() != "")
				c->setReplyBuffer(RPL_WELCOME(c->getNickname(), c->getNickname(), c->getUsername(), c->getHostname()));	
	}
}
