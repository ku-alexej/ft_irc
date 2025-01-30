/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdPASS.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:57:28 by akurochk          #+#    #+#             */
/*   Updated: 2025/01/30 15:54:33 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::cmdPass(std::vector<std::string> tokens, int fd) {
	Client *c = getClientByFd(fd);
	
	if(c->getPassOk()) {
		c->setReplyBuffer(ERR_ALREADYREGISTERED(c->getNickname()));
		return ;
	}

	if(tokens.size() < 2 || tokens[1] == "") {
		c->setReplyBuffer(ERR_NEEDMOREPARAMS(c->getNickname(), tokens[0]));
		return ;
	}

	if(tokens[1] != _password) {
		c->setReplyBuffer(ERR_PASSWDMISMATCH(c->getNickname()));					// WE MUST KICK IT
		return ;
	}

	c->setPassOk(true);
	
	if(c->getPassOk() && c->getNickname() != "" && c->getUsername() != "", !c->getCapOn())
		c->setReplyBuffer(RPL_WELCOME(c->getNickname(), c->getNickname(), c->getUsername(), c->getHostname()));
}
