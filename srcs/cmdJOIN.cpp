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
#define RESET   "\033[0m"
#define RED     "\033[31m"  // Outer vector
#define GREEN   "\033[32m"  // Subvector
#define YELLOW  "\033[33m"  // Individual strings

// Channel* Server::getChannel(std::string &chanName) {
//     // parse the chan
// }

bool isValidChannelName(const std::string &channel) {
    if (channel.empty())
        return false;
    char firstChar = channel[0];
    return (firstChar == '#' || firstChar == '&');
}

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// use (getChannel(name) == NULL) instead of this function and getChannels()
bool Server::channelExists( std::string channelName)
{
    std::vector<Channel> allChannels = this->getChannels();
    for (std::vector<Channel>::iterator it = allChannels.begin(); it != allChannels.end(); it++) {
        std::cout << "we are here" << std::endl;
        if ((it)->getName() == channelName) {
            std::cout << RED << "Channel found, joining channel." << RESET << std::endl;
            return true;
        }
    }
    std::cout << RED << "Channel NOT found, joining channel." << RESET << std::endl;
    return false;
    
}

static void    joinRpl(Client *client, Channel *channel)
{
    client -> setReplyBuffer(client -> getUserID() + " JOIN " + channel->getName());
    if (!channel -> getTopicText().empty())
        client -> setReplyBuffer(RPL_TOPIC(client -> getNickname(), channel -> getName(), channel -> getTopicText()));
    

    
    // std::stringstream ss;
    // std::string prefix;
    // ss << RPL_NAMREPLY(client.getNickname(), "=", channel.getName());
    // for (std::map<std::string, Client*>::iterator it = channel.getAllMembers().begin(); it != channel.getAllMembers().end(); it++)
    // {
    //     prefix = getPrefix(*it->second, channel);
    //     if (it != channel.getAllMembers().begin())
    //         ss << " ";
    //     ss << prefix << it->first;
    // }fjnvdjs djdnb
    // ss << CRLF;
    // client.addToWriteBuffer(ss.str());
    // client.addToWriteBuffer(RPL_ENDOFNAMES(client.getNickname(), channel.getName()));
}

void    Server::joinChannel(Client *client, std::string channelName, std::string key)
{

    (void) key;
    
    // bool ifExists = channelExists(channelName);
    bool isExists = getChannel(channelName) != NULL;
    std::cout << "CHAN EXISTS=:" << isExists << std::endl;
    if (isExists == true)
    {
        std::cout << "CHAN EXISTS == true"  << std::endl;

        //ERRORS MANAGEMENT
        Channel *channel = this->getChannel(channelName);
        channel->addClient(client);
        client -> addChannel(channelName);
        joinRpl(client,channel);
        // channel->addMember(&ctx._client);
        // ctx._client.addChannel(channelName); // add new channel to clientś list of channels they are currently in
        // joinRpl(ctx._client, *channel);
        // channel->sendToAll(ctx._client.getNickname(), ctx._client.getUserID() + " JOIN " + channel->getName() + CRLF);
        // if (channel->isInvited(ctx._client.getNickname()))
        //     channel->removeInvitedUser(ctx._client.getNickname());
    }
    else
    {
        std::cout << "CHAN EXISTS != true" << std::endl;

        Channel newChannel(channelName, client, true);
        client -> addChannel(channelName);
        this->addChannel(&newChannel, channelName);
        newChannel.addClient(client);
        joinRpl(client,&newChannel);
    }


}

void Server::cmdJoin(std::vector<std::string> tokens, int fd) {
    Client* c = getClientByFd(fd);
    if (!c) {
        // Handle error: client not found
        return;
    }

    if (tokens.size() < 2) {
        c->setReplyBuffer(ERR_NEEDMOREPARAMS(c->getNickname(), tokens[0]));
        return;
    }
    // channelNames.size()
    if (tokens.size() > 10) {
        c->setReplyBuffer(ERR_NEEDMOREPARAMS(c->getNickname(), tokens[0]));
        return;
    }
    std::cout << "hello" << std::endl;
    printStringVector(tokens);
    std::vector<std::string> channels = split(tokens[1], ',');
    std::vector<std::string> keys;
    if (tokens.size() >= 3) {
        keys = split(tokens[2], ',');
    }
    
    std::map<std::string, std::string> channelMap;
    for (std::size_t i = 0; i < channels.size(); ++i) {
        std::string channel = channels[i];
         if (!isValidChannelName(channel)) {
            continue;
        }
        std::string password = (i < keys.size()) ? keys[i] : "";
        channelMap[channel] = password;
    }
    
    
    for (std::map<std::string, std::string>::iterator it = channelMap.begin();
         it != channelMap.end(); ++it)
    {
         std::cout << "[INFO]: Channel: " << it->first
                   << ", Password: " << (it->second.empty() ? "(none)" : it->second)
                   << std::endl;
    }

    for (std::map<std::string, std::string>::iterator it = channelMap.begin(); it != channelMap.end(); ++it)
    {

        // here we must sent pointer (not pointer to pointer)
        joinChannel(c, it->first, it->second);
          // For each channel, perform the join operation.
        // This function should handle:
        //   - Checking if the channel exists.
        //   - Creating the channel if it doesn't exist.
        //   - Verifying if the client is allowed to join (permissions, ban list, etc.).
        //   - Adding the client to the channel.
        //   - Sending the necessary notifications.
    }
}