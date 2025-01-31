/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdMODE.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:11:10 by akurochk          #+#    #+#             */
/*   Updated: 2025/01/31 15:39:39 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::cmdUserMode(std::vector<std::string> tokens, int fd) {
	Client *c = getClientByFd(fd);
	Client *t = getClientByNick(tokens[1]);
	
	if (t == NULL) {
		c->setReplyBuffer(ERR_NOSUCHNICK(c->getNickname(), tokens[1]));
		return ;
	}

	if (c->getNickname() != tokens[1]) {
		c->setReplyBuffer(ERR_USERSDONTMATCH(c->getNickname()));
		return ;
	}

	if (tokens.size() == 2) {
		c->setReplyBuffer(RPL_UMODEIS(c->getNickname(), ""));
		return ;
	}

	c->setReplyBuffer(ERR_UMODEUNKNOWNFLAG(c->getNickname()));
}

void	Server::cmdChannelMode(std::vector<std::string> tokens, int fd) {
	(void) tokens;
	(void) fd; 
}

void	Server::cmdMode(std::vector<std::string> tokens, int fd) {

	Client *c = getClientByFd(fd);

	if(tokens.size() < 2 || tokens[1].empty()) {
		c->setReplyBuffer(ERR_NEEDMOREPARAMS(c->getUsername(), tokens[0]));
		return ;
	}
	
	// MODE for client: we have +i in irssi afer registration
	if(tokens[1][0] != '#') {
		cmdUserMode(tokens, fd);
		return ;
	}
	
	// MODE for channel: as in subject
	if(tokens[1][0] == '#') {
		cmdChannelMode(tokens, fd);
		return ;
	}
}
