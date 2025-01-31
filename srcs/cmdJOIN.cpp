/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdJOIN.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:11:06 by akurochk          #+#    #+#             */
/*   Updated: 2025/01/30 18:30:36 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#define RESET   "\033[0m"
#define RED     "\033[31m"  // Outer vector
#define GREEN   "\033[32m"  // Subvector
#define YELLOW  "\033[33m"  // Individual strings

Channel* Server::getChannel(std::string &chanName) {
    // parse the chan
}

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


void    joinChannel(Client client, std::string &channelName, std::string &key)
{
    // get chan
    // if there -> join
    // if not
    // create
    std::cout << "j" << std::endl;
}

void Server::cmdJoin(std::vector<std::string> tokens, int fd) {
    Client* c = getClientByFd(fd);
    if (!c) {
        // Handle error: client not found
        return;
    }

    if (tokens.size() < 2) {
        // Send error: No channel name provided
        c->setReplyBuffer(ERR_NEEDMOREPARAMS(c->getNickname(), tokens[0]));
        return;
    }
    if (tokens.size() > 10) {
        //too much chafns, verify if it's okay 
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
          // For each channel, perform the join operation.
        // This function should handle:
        //   - Checking if the channel exists.
        //   - Creating the channel if it doesn't exist.
        //   - Verifying if the client is allowed to join (permissions, ban list, etc.).
        //   - Adding the client to the channel.
        //   - Sending the necessary notifications.
    }
}