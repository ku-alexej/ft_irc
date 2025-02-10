/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdPART.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:11:12 by akurochk          #+#    #+#             */
/*   Updated: 2025/02/10 14:08:29 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::deleteEmptyChannel(Channel *channel) {

	if (channel->getClients().size() == 0) {
		std::vector<Client *> clients = channel->getClients();
		for (std::vector<Client *>::iterator it = clients.begin(); it != clients.end(); ++it) {
			(*it)->deleteInvite(channel->getName());
		}
		deleteChannel(channel->getName());
	}
}

void	Server::cmdPart(std::vector<std::string> tokens, int fd) {

	Client						*c = getClientByFd(fd);
	Channel						*channel;
	std::string					reason;
	std::vector<std::string>	channelsNames;

	if (c->getRegistred() == false) {
		c->setReplyBuffer(ERR_NOTREGISTERED(c->getNickname()));
		return ;
	}

	if (tokens.size() < 2) {
		c->setReplyBuffer(ERR_NEEDMOREPARAMS(c->getUsername(), tokens[0]));
		return;
	}

	if (tokens.size() > 2) {
		for (size_t i = 2; i < tokens.size(); ++i) {
			if (i != 2) {
				reason += " ";
			}
			reason += tokens[i];
		}
	}
	reason.erase(0, 1);

	channelsNames = split(tokens[1], ',');
	for (size_t i = 0; i < channelsNames.size(); i++) {
		channel = getChannel(channelsNames[i]);

		if (channel == NULL) {
			c->setReplyBuffer(ERR_NOSUCHCHANNEL(c->getNickname(), channelsNames[i]));
			return;
		}

		if (channel->getClientByFd(c->getFd()) == NULL) {
			c->setReplyBuffer(ERR_NOTONCHANNEL(c->getNickname(), channelsNames[i]));
			return;
		}

		std::stringstream msg;
		msg << c->getUserID() << " PART " << channel->getName() << " :" << reason;

		c->deleteChannel(channelsNames[i]);
		channel->deleteOperator(c);
		channel->deleteClient(c);

		c->setReplyBuffer(msg.str());
		channel->setReplyBufferForAllChannelClients(msg.str());

		deleteEmptyChannel(channel);
	}
}
