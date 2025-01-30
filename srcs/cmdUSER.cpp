/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdUSER.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:57:31 by akurochk          #+#    #+#             */
/*   Updated: 2025/01/30 15:55:00 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void 	Server::cmdUser(std::vector<std::string> tokens, int fd) {

	Client *c = getClientByFd(fd);
	
	//check the name/nick is set
	if (tokens.size() < 5) {
		c->setReplyBuffer(ERR_NEEDMOREPARAMS(c->getNickname(), tokens[0]));
		return ;
	}

	if (c->getUsername() != "") {
		c->setReplyBuffer(ERR_ALREADYREGISTERED(c->getNickname()));
		return ;
	}

	if(tokens[4][0] == ':')
		tokens[4].erase(tokens[4].begin());

	std::string realname = tokens[4];
	for (size_t i = 5; i < tokens.size(); i++)
		realname = realname + " " + tokens[i];
	
	c->setUsername(tokens[1]);
	c->setHostname(tokens[2]);
	c->setServername(tokens[3]);
	c->setRealname(realname);
	
	if(c->getPassOk() && c->getNickname() != "" && c->getUsername() != "", !c->getCapOn())
		c->setReplyBuffer(RPL_WELCOME(c->getNickname(), c->getNickname(), c->getUsername(), c->getHostname()));
}
