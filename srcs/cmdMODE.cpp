/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdMODE.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:11:10 by akurochk          #+#    #+#             */
/*   Updated: 2025/01/31 16:55:33 by akurochk         ###   ########.fr       */
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
	// ERR_NOSUCHCHANNEL (403)
	// RPL_CREATIONTIME (329)		-- optional, can skip it
	// RPL_CHANNELMODEIS (324)
	// ERR_CHANOPRIVSNEEDED (482)

	// When the server is done processing the modes, 
	// a MODE command is sent to all members of the channel containing the mode changes.

	// +i [---]
	// -i [---]
	// +t [---]
	// -t [---]
	// +k [password to set]
	// -k [current password]
	// +o [nickname to give op rights]
	// -o [nickneme to remove op rights]
	// +l [user limit]
	// -l [---]
	
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
