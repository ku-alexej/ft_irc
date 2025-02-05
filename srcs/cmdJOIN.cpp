/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdJOIN.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:11:06 by akurochk          #+#    #+#             */
/*   Updated: 2025/02/04 18:54:18 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// std::vector<std::string> split(const std::string &str, char delimiter)
// {
//     std::vector<std::string> tokens;
//     std::stringstream ss(str);
//     std::string token;
//     while (std::getline(ss, token, delimiter))
//     {
//         tokens.push_back(token);
//     }
//     return tokens;
// }

// std::string getPrefix(Client *client, Channel *channel)
// {
//     std::vector<Client *> operators = channel->getOperators();
//     for (std::vector<Client *>::iterator it = operators.begin(); it != operators.end(); ++it)
//     {
//         if ((*it)->getNickname() == client->getNickname())
//             return "@";
//     }
//     return "";
// }

// static void joinRpl(Client *client, Channel *channel)
// {
//     client->setReplyBuffer(client->getUserID() + " JOIN " + channel->getName() + "\r\n");

//     if (!channel->getTopicText().empty())
//         client->setReplyBuffer(RPL_TOPIC(client->getNickname(), channel->getName(), channel->getTopicText()));

//     std::stringstream nickListStream;
//     std::vector<Client *> clients = channel->getClients();
//     bool first = true;
//     for (std::vector<Client *>::iterator it = clients.begin(); it != clients.end(); ++it)
//     {
//         if (!first)
//             nickListStream << " ";
//         else
//             first = false;
//         nickListStream << getPrefix(*it, channel) << (*it)->getNickname();
//     }

//     std::string nickList = nickListStream.str();
//     std::stringstream ss;
//     ss << RPL_NAMREPLY(client->getNickname(), "=", channel->getName(), nickList) << "\r\n";

//     client->setReplyBuffer(ss.str());
//     client->setReplyBuffer(RPL_ENDOFNAMES(client->getNickname(), channel->getName()));
// }

// bool isMember(std::string channelName, std::vector<std::string> clientChannels)
// {
//     for (std::vector<std::string>::iterator it = clientChannels.begin(); it != clientChannels.end(); ++it)
//     {
//         if (*it != channelName)
//         {
//             return true;
//         }
//     }
//     return false;
// }

// std::string Channel::getPass() { return this->_password;}

// void Server::joinChannel(Client *client, std::string channelName, std::string key)
// {

//     std::vector<std::string> clientChannels = client->getChannelNames();
//     (void) key;
//     if (getChannel(channelName) != NULL)
//     {
//         // ERRORS MANAGEMENT
//         Channel *channel = this->getChannel(channelName);
//         // I am not sure that ISMember is needed
//         // if (!(isMember(channelName, clientChannels)))
//         //     client->setReplyBuffer(ERR_BADCHANNELKEY(client->getNickname(), channelName));
//         // if (channel -> getPass() != key &&  key!= "")
//         //     client->setReplyBuffer(ERR_BADCHANNELKEY(client->getNickname(), channelName));
//         //  Check if channel is invite-only and the client is not invited.
//         // Check if channel is password-protected and key is incorrect.
//         //  Check if channel is full.
//         // Check if client is banned.

//         channel->addClient(client);
//         client->addChannel(channelName);
//         joinRpl(client, channel);
//         channel -> broadcastJoinMessage(client);
//     }
//     else
//     {

//         Channel *newChannel = new Channel(channelName, client, true); // key-word 'new' allocates memory, welcome to the memory-leaks party ^.^
//         client->addChannel(channelName);
//         this->addChannel(newChannel, channelName);
//         newChannel->addClient(client);
//         newChannel->addOperator(client);                            // it is new channel so we should add the client to _clients and to _operators
//         joinRpl(client, newChannel);
//     }
// }

// void Server::cmdJoin(std::vector<std::string> tokens, int fd)
// {
//     Client *c = getClientByFd(fd);
//     if (!c)
//     {
//         // Handle error: client not found
//         return;
//     }

//     if (tokens.size() < 2)
//     {
//         c->setReplyBuffer(ERR_NEEDMOREPARAMS(c->getNickname(), tokens[0]));
//         return;
//     }
//     if (c->getChannelNames().size() > 10)
//     {
//         c->setReplyBuffer(ERR_TOOMANYCHANNELS(c->getNickname(), tokens[0]));
//         return;
//     }
//     std::vector<std::string> channels = split(tokens[1], ',');
//     std::vector<std::string> keys;
//     if (tokens.size() >= 3)
//     {
//         keys = split(tokens[2], ',');
//     }

//     std::map<std::string, std::string> channelMap;
//     for (std::size_t i = 0; i < channels.size(); ++i)
//     {
//         std::string channel = channels[i];
//         if (!isValidChannelName(channel))
//         {
//             c->setReplyBuffer(ERR_BADCHANMASK(channel));
//             continue;
//         }

//         std::string password = (i < keys.size()) ? keys[i] : "";
//         channelMap[channel] = password;
//     }

//     for (std::map<std::string, std::string>::iterator it = channelMap.begin(); it != channelMap.end(); ++it)
//     {
//         joinChannel(c, it->first, it->second);
//     }
// }

std::vector<std::string>	split(const std::string str, char delimiter) {
    std::vector<std::string> v;
    std::stringstream ss(str);
    std::string element;

    while (std::getline(ss, element, delimiter)) {
        v.push_back(element);
    }

    return (v);
}

std::vector<std::pair<std::string, std::string> >   Server::getChannelsToJoin(std::vector<std::string> tokens) {
    std::vector<std::pair<std::string, std::string> > channelsToJoin;
	std::vector<std::string> channelsNames;     
	std::vector<std::string> channelsKeys;
    
    channelsNames = split(tokens[1], ',');
    if (tokens.size() > 2) {
        channelsKeys = split(tokens[2], ',');
    }

	std::cout << "[INFO]: JOIN names=";
	printStringVector(channelsNames);

    if (tokens.size() > 2) {
        std::cout << "[INFO]: JOIN passs=";
        printStringVector(channelsKeys);
    }

    std::cout << "[DEBUG]: ----------- -1" << std::endl;

    for (size_t i = 0; i < channelsNames.size(); i++) {
        if (i < channelsKeys.size() && !channelsKeys[i].empty()) {
            channelsToJoin.push_back(std::make_pair(channelsNames[i], channelsKeys[i]));
        } else {
            channelsToJoin.push_back(std::make_pair(channelsNames[i], ""));
        }
    }

    std::cout << "[DEBUG]: ----------- 0" << std::endl;

    return (channelsToJoin);
}

void    Server::welcomeChannelReply(Client *c, Channel *ch) {

    c->setReplyBuffer(JOIN_OK(c->getNickname(), c->getNickname(), c->getHostname(), ch->getName()));

    if (!ch->getTopicText().empty()) {
        c->setReplyBuffer(RPL_TOPIC(c->getNickname(), ch->getName(), ch->getTopicText()));
    }

    std::string clientsList;
    for (size_t i = 0; i < ch->getClients().size(); i++) {
        if (ch->getOperatorByFd(c->getFd()) != NULL) {
            clientsList += "@";
        }
        
        clientsList += c->getNickname();

        if (i < ch->getClients().size()) {
            clientsList += " ";
        }
    }
    c->setReplyBuffer(RPL_NAMREPLY(c->getNickname(), "=", ch->getName(), clientsList));

    c->setReplyBuffer(RPL_ENDOFNAMES(c->getNickname(), ch->getName()));
}

bool Server::createChannel(Client *c, Channel *newChannel, std::string channelName) {

    std::cout << "[DEBUG]: >>> 0" << std::endl;
    if (c->getChannelNames().size() >= 10) {
        c->setReplyBuffer(ERR_TOOMANYCHANNELS(c->getNickname(), channelName));
        return (false);
    }

    std::cout << "[DEBUG]: >>> 1" << std::endl;
    if (isValidChannelName(channelName) != true) {
        c->setReplyBuffer(ERR_BADCHANMASK(channelName));
        return (false);
    }

    std::cout << "[DEBUG]: >>> 2" << std::endl;
    newChannel->setName(channelName);
    std::cout << "[DEBUG]: >>> 3" << std::endl;
    newChannel->addClient(c);
    std::cout << "[DEBUG]: >>> 4" << std::endl;
    newChannel->addOperator(c);

    std::cout << "[DEBUG]: >>> 5" << std::endl;
    c->addChannel(channelName);

    std::cout << "[DEBUG]: >>> 6" << std::endl;
    welcomeChannelReply(c, newChannel);  

    std::cout << "[DEBUG]: >>> 7" << std::endl;

    return (true);  
}

void    Server::joinChannel(Client *c, std::string channelName, std::string key) {
    (void) c;
    (void) channelName;
    (void) key;
}

void Server::cmdJoin(std::vector<std::string> tokens, int fd) {
    Client *c = getClientByFd(fd);
    Channel newChannel;

	// not enough params
    if (tokens.size() < 2) {
        c->setReplyBuffer(ERR_NEEDMOREPARAMS(c->getUsername(), tokens[0]));
    }

	// too much params
    if (tokens.size() > 3) {
        c->setReplyBuffer(ERR_NEEDMOREPARAMS(c->getUsername(), tokens[0]));
    }

    std::cout << "[DEBUG]: ----------- -7" << std::endl;
    std::vector<std::pair<std::string, std::string> > channelsToJoin = getChannelsToJoin(tokens);
    std::cout << "[DEBUG]: ----------- 1" << std::endl;


    for (size_t i = 0; i < channelsToJoin.size(); i++) {
        if (getChannel(channelsToJoin[i].first) == NULL) {
            // создать новый
            std::cout << "[DEBUG]: ----------- new" << std::endl;
            if (createChannel(c, &newChannel, channelsToJoin[i].first) == true) {
                _channels.push_back(&newChannel);
            }
        } else {
            // присоедениться
            std::cout << "[DEBUG]: ----------- join" << std::endl;
            joinChannel(c, channelsToJoin[i].first, channelsToJoin[i].second);
        }
    }

}
