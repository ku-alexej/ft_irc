/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdTOPIC.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:11:17 by akurochk          #+#    #+#             */
/*   Updated: 2025/01/30 18:31:05 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::cmdTopic(std::vector<std::string> tokens, int fd)
{
    std::string channelName = tokens[1];
    std::string comment;
    Client *c = getClientByFd(fd);

    if (tokens.size() < 2)
    {
        c->setReplyBuffer(ERR_NEEDMOREPARAMS(c->getNickname(), tokens[0]));
        return;
    }

    if (tokens.size() > 2)
    {
        for (size_t i = 2; i < tokens.size(); ++i)
        {
            if (i != 2)
            {
                comment += " ";
            }
            comment += tokens[i];
        }
    }

    Channel *channel = getChannel(channelName);
    if (!channel)
    {
        c->setReplyBuffer(ERR_NOSUCHCHANNEL(c->getNickname(), channelName));
        return;
    }

    if (!channel->getClientByFd(c->getFd()))
    {
        c->setReplyBuffer(ERR_NOTONCHANNEL(c->getNickname(), channelName));
        return;
    }

    if (channel->getT() && channel->getOperatorByFd(c->getFd()) == NULL)
    {
        c->setReplyBuffer(ERR_CHANOPRIVSNEEDED(c->getNickname(), channelName));
        return;
    }

    if (tokens.size() > 2)
    {
        channel->setTopicText(comment);

        std::stringstream ss;
        ss << c->getUserID() << " TOPIC " << channelName << " : " << comment;
        channel->setReplyBufferForAllChannelClients(ss.str());

    }	
    else  
    {
        if (!channel->getTopicText().empty())
        {
            c->setReplyBuffer(RPL_TOPIC(c->getNickname(), channelName, channel->getTopicText()));
        }
        else
        {
            c->setReplyBuffer(RPL_NOTOPIC(c->getNickname(), channelName));
        }
    }
}