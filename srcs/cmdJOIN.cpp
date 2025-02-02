/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdJOIN.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:11:06 by akurochk          #+#    #+#             */
/*   Updated: 2025/02/01 17:42:46 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

bool isValidChannelName(const std::string &channel)
{
    if (channel.empty())
        return false;

    char firstChar = channel[0];
    if (firstChar != '#')
        return false;

    for (std::size_t i = 0; i < channel.size(); ++i)
    {
        char c = channel[i];
        if (c == ' ' || c == '\a' || c == ',')
            return false;
    }

    return true;
}

std::vector<std::string> split(const std::string &str, char delimiter)
{
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

bool Server::channelExists(std::string channelName)
{
    if ((getChannel(channelName) == NULL))
        return false;
    return true;
}

std::string getPrefix(Client *client, Channel *channel)
{
    std::vector<Client *> operators = channel->getOperators();
    for (std::vector<Client *>::iterator it = operators.begin(); it != operators.end(); ++it)
    {
        if ((*it)->getNickname() == client->getNickname())
            return "@";
    }
    return "";
}

static void joinRpl(Client *client, Channel *channel)
{
    client->setReplyBuffer(client->getUserID() + " JOIN " + channel->getName() + "\r\n");

    if (!channel->getTopicText().empty())
        client->setReplyBuffer(RPL_TOPIC(client->getNickname(), channel->getName(), channel->getTopicText()));

    std::stringstream nickListStream;
    std::vector<Client *> clients = channel->getClients();
    bool first = true;
    for (std::vector<Client *>::iterator it = clients.begin(); it != clients.end(); ++it)
    {
        if (!first)
            nickListStream << " ";
        else
            first = false;
        nickListStream << getPrefix(*it, channel) << (*it)->getNickname();
    }

    std::string nickList = nickListStream.str();
    std::stringstream ss;
    ss << RPL_NAMREPLY(client->getNickname(), "=", channel->getName(), nickList) << "\r\n";

    client->setReplyBuffer(ss.str());
    client->setReplyBuffer(RPL_ENDOFNAMES(client->getNickname(), channel->getName()));
}

bool isMember(std::string channelName, std::vector<std::string> clientChannels)
{
    for (std::vector<std::string>::iterator it = clientChannels.begin(); it != clientChannels.end(); ++it)
    {
        if (*it != channelName)
        {
            return true;
        }
    }
    return false;
}

std::string Channel::getPass() { return this->_password;}

void Server::joinChannel(Client *client, std::string channelName, std::string key)
{

    std::vector<std::string> clientChannels = client->getChannelNames();
    bool isExists = getChannel(channelName) != NULL;
    (void) key;
    if (isExists == true)
    {
        // ERRORS MANAGEMENT
        Channel *channel = this->getChannel(channelName);
        // I am not sure that ISMember is needed
        // if (!(isMember(channelName, clientChannels)))
        //     client->setReplyBuffer(ERR_BADCHANNELKEY(client->getNickname(), channelName));
        // if (channel -> getPass() != key &&  key!= "")
        //     client->setReplyBuffer(ERR_BADCHANNELKEY(client->getNickname(), channelName));
        //  Check if channel is invite-only and the client is not invited.
        // Check if channel is password-protected and key is incorrect.
        //  Check if channel is full.
        // Check if client is banned.

        channel->addClient(client);
        client->addChannel(channelName);
        joinRpl(client, channel);
        channel -> broadcastJoinMessage(client);
    }
    else
    {

        Channel *newChannel = new Channel(channelName, client, true);
        client->addChannel(channelName);
        this->addChannel(newChannel, channelName);
        newChannel->addClient(client);
        joinRpl(client, newChannel);
    }
}

void Server::cmdJoin(std::vector<std::string> tokens, int fd)
{
    Client *c = getClientByFd(fd);
    if (!c)
    {
        // Handle error: client not found
        return;
    }

    if (tokens.size() < 2)
    {
        c->setReplyBuffer(ERR_NEEDMOREPARAMS(c->getNickname(), tokens[0]));
        return;
    }
    if (c->getChannelNames().size() > 10)
    {
        c->setReplyBuffer(ERR_TOOMANYCHANNELS(c->getNickname(), tokens[0]));
        return;
    }
    std::vector<std::string> channels = split(tokens[1], ',');
    std::vector<std::string> keys;
    if (tokens.size() >= 3)
    {
        keys = split(tokens[2], ',');
    }

    std::map<std::string, std::string> channelMap;
    for (std::size_t i = 0; i < channels.size(); ++i)
    {
        std::string channel = channels[i];
        if (!isValidChannelName(channel))
        {
            c->setReplyBuffer(ERR_BADCHANMASK(channel));
            continue;
        }

        std::string password = (i < keys.size()) ? keys[i] : "";
        channelMap[channel] = password;
    }

    for (std::map<std::string, std::string>::iterator it = channelMap.begin(); it != channelMap.end(); ++it)
    {
        joinChannel(c, it->first, it->second);
    }
}