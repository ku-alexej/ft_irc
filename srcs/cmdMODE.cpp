/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdMODE.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:11:10 by akurochk          #+#    #+#             */
/*   Updated: 2025/02/01 16:19:26 by akurochk         ###   ########.fr       */
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

	// -i [---]
	// +i [---]								>> ERR_INVITEONLYCHAN (473)

	// -t [---]
	// +t [---]								>> ERR_NEEDMOREPARAMS (461)
	//										>> ERR_NOSUCHCHANNEL (403)
	//										>> ERR_NOTONCHANNEL (442)
	//										>> ERR_CHANOPRIVSNEEDED (482)
	//										>> RPL_NOTOPIC (331)
	//										>> RPL_TOPIC (332) + RPL_TOPICWHOTIME (333)

	// -k [current password]
	// +k [password to set]					>> ERR_INVALIDMODEPARAM ()
	//										>> ERR_INVALIDKEY ()
	//										>> ERR_BADCHANNELKEY (475)

	// -o [nickneme to remove op rights]
	// +o [nickname to give op rights]		>> This mode is standard. The prefix and mode letter used for it, respectively, are "@" and "+o".
	//										>> Users with this mode may perform channel moderation tasks such as kicking users, applying channel modes,
	//										>> and set other users to operator (or lower) status.

	// -l [---]
	// +l [user limit]						>> ERR_CHANNELISFULL (471)
	
	Client	*c = getClientByFd(fd);
	Channel	*ch = getChannelByName(tokens[1]);

	if (ch == NULL) {
		c->setReplyBuffer(ERR_NOSUCHCHANNEL(c->getNickname(), tokens[1]));
		return ;
	}

	if (tokens.size() == 2) {
		c->setReplyBuffer(RPL_CHANNELMODEIS(c->getNickname(), ch->getName(), ch->getModes(), ch->getModesArgs(ch->getClientByFd(fd) != NULL)));
		return ;
	}

	if (ch->getOperatorByFd(fd) == NULL) {
		c->setReplyBuffer(ERR_CHANOPRIVSNEEDED(c->getNickname(), tokens[1]));
		return ;
	}
	
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
