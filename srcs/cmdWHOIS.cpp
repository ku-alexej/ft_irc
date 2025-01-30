/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdWHOIS.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:57:16 by akurochk          #+#    #+#             */
/*   Updated: 2025/01/30 17:35:41 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// ERR_NOSUCHNICK (401)
// ERR_NOSUCHSERVER (402)
// ERR_NONICKNAMEGIVEN (431)


// Possible PLYs. Most are useless for us.
//	RPL_WHOISCERTFP (276)
//	RPL_WHOISREGNICK (307)
//	RPL_WHOISUSER (311)			// to use as our reply
//	RPL_WHOISSERVER (312)
//	RPL_WHOISOPERATOR (313)
//	RPL_WHOISIDLE (317)
//	RPL_ENDOFWHOIS (318) 		// to finilize the reply
//	RPL_WHOISCHANNELS (319)
//	RPL_WHOISSPECIAL (320)
//	RPL_WHOISACCOUNT (330)
//	RPL_WHOISACTUALLY (338)
//	RPL_WHOISHOST (378)
//	RPL_WHOISMODES (379)
//	RPL_WHOISSECURE (671)
//	RPL_AWAY (301)


void	Server::cmdWhois(std::vector<std::string> tokens, int fd) {
	Client *c = getClientByFd(fd);
	Client *t;
	
	if (tokens.size() < 2 || tokens[1].empty()) {
		c->setReplyBuffer(ERR_NONICKNAMEGIVEN(c->getNickname()));
		return ;
	}

	if (tokens.size() >= 3  && tokens[1] != _serverName && tokens[1] != tokens[1]) {
		c->setReplyBuffer(ERR_NOSUCHSERVER(c->getNickname(), tokens[1]));
		return ;
	}
	
	(tokens.size() >= 3) ? t = getClientByNick(tokens[2]) : t = getClientByNick(tokens[1]);

	if (t == NULL) {
		c->setReplyBuffer(ERR_NOSUCHNICK(c->getNickname(), ((tokens.size() >= 3) ? tokens[2] : tokens[1])));
		return ;
	}
	
	c->setReplyBuffer(RPL_WHOISUSER(c->getNickname(), t->getNickname(), t->getUsername(), t->getHostname(), t->getRealname()));
	// here we can set more RPLs to the replyBuffer if we want to give more info to client
	c->setReplyBuffer(RPL_ENDOFWHOIS(c->getNickname(), c->getNickname()));
}
