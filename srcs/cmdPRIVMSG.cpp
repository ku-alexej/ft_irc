#include "Server.hpp"

void Server::cmdPrivmsg(std::vector<std::string> tokens, int fd)
{
    Client *c = getClientByFd(fd);

    if (tokens.size() == 1)
    {
        c->setReplyBuffer(ERR_NORECIPIENT(c->getNickname(), tokens[0]));
        return;
    }
    if (tokens.size() < 3)
    {
        c->setReplyBuffer(ERR_NOTEXTTOSEND(c->getNickname()));
        return;
    }

    std::string message;
    if (tokens[2][0] == ':')
    {
        tokens[2].erase(tokens[2].begin());
        for (size_t i = 2; i < tokens.size(); ++i)
        {
            if (i != 2)
            {
                message += " ";
            }
            message += tokens[i];
        }
        std::vector<std::string> targets = split(tokens[1], ',');
       for (size_t i = 0; i < targets.size(); ++i)
        {
            std::string target = targets[i];
            
            if (target.find('#') != std::string::npos)
            {
                bool operators = false;

                for (std::string::iterator it = target.begin(); it != target.end() && *it != '#'; ++it)
                {
                    if (*it == '@')
                    {
                        operators = true;
                        break;
                    }
                }
                
                size_t pos = target.find('#');
                std::string channelName = target.substr(pos);
                Channel *channel = getChannel(channelName);
                if (!channel)
                {
                    c->setReplyBuffer(ERR_NOSUCHCHANNEL(c->getNickname(), channelName));
                    continue;
                }
                else if (!channel->getClientByFd(c->getFd()))
                {
                    c->setReplyBuffer(ERR_NOTONCHANNEL(c->getNickname(), channelName));
                    continue;
                }
                
                std::stringstream ss;
                ss << c ->getUserID() << " PRIVMSG " << channel -> getName() << " :" << message;
                
                if (operators)
                    continue;
                else
                    channel->setReplyBufferForAllChannelClients(ss.str());
            }
            else
            {
                Client *recipient = getClientByNick(target); 

                if (!recipient)
                {
                    c->setReplyBuffer(ERR_NOSUCHNICK(c->getNickname(), target)); 
                    continue;  
                }

                std::stringstream ss;
                ss << c->getNickname() << " PRIVMSG " << recipient -> getNickname() << " :" << message;
                recipient->setReplyBuffer(ss.str()); 
            }
        }
    }
}
