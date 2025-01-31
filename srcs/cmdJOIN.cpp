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


// Split helper
std::vector<std::string> split(const std::string& str) {
    std::vector<std::string> tokens;
    std::istringstream ss(str);
    std::string token;
    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
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
        //too much chans
        c->setReplyBuffer(ERR_NEEDMOREPARAMS(c->getNickname(), tokens[0]));
        return;
    }
    std::cout << "print RAW" << std::endl;
     printBuffer(c -> getRawCmds());
    // Iterate over all tokens starting from index 1
 
    //  std::map<std::string, std::string>::iterator it;
    // for (it = channelMap.begin(); it != channelMap.end(); ++it) {
    //     std::string chan = it->first;
    //     std::string pass = it->second;
    //     // Handle joining 'chan' with 'pass'
    //     // Example:
    //     // joinChannel(c, chan, pass);

    //     // Print channel and password
    //     std::cout << "[INFO]: Channel: " << chan << ", Password: " << pass << std::endl;
    // }
}