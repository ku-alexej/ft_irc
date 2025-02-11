#include "Server.hpp"

void Server::cmdPrivmsg(std::vector<std::string> tokens, int fd)
{
    Client *c = getClientByFd(fd);

    if (tokens.size() < 3)
    {
        c->setReplyBuffer(ERR_NOTEXTTOSEND(c->getNickname())); 
        return;
    }

    std::string message;
    for (size_t i = 2; i < tokens.size(); ++i)
    {
        if (i != 2)
        {
            message += " ";  // Add space between tokens
        }
        message += tokens[i];  // Concatenate the message parts
    }

    std::vector<std::string> targets = split(tokens[1], ',');

    for (size_t i = 0; i < targets.size(); ++i)
    {
        std::string target = targets[i];

        if (target[0] == '#')
        {
            Channel *channel = getChannel(target); 

            if (!channel)
            {
                c->setReplyBuffer(ERR_NOSUCHCHANNEL(c->getNickname(), target)); 
                continue;  
            }
            
            if (!channel->getClientByFd(c->getFd()))
            {
                c->setReplyBuffer(ERR_NOTONCHANNEL(c->getNickname(), target)); // Error if not a member
                continue;
            }

            if (channel->getT() && !channel->getOperatorByFd(c->getFd()))
            {
                c->setReplyBuffer(ERR_CANNOTSENDTOCHAN(c->getNickname(), target)); // Error if not an operator in a moderated channel
                continue;
            }

            std::stringstream ss;
            ss << c->getNickname() << " PRIVMSG " << target << " :" << message << CRLF;
            channel->setReplyBufferForAllChannelClients(ss.str());  // Send the message to all channel clients
        }
        else  
        {
            // Client *recipient = getClientByNick(target); // Find the client by nickname
            
            // if (!recipient)
            // {
            //     c->setReplyBuffer(ERR_NOSUCHNICK(c->getNickname(), target)); // Error if user doesn't exist
            //     continue;  // Move to the next target
            // }

            // // Send the message to the recipient
            // std::stringstream ss;
            // ss << c->getNickname() << " PRIVMSG " << target << " :" << message << CRLF;
            // recipient->addToWriteBuffer(ss.str()); // Send the message to the recipient
        }
    }
}
