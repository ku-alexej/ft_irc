#include "Server.hpp"

// void Server::cmdPrivmsg(std::vector<std::string> tokens, int fd)
// {
//     // Client *c = getClientByFd(fd);

//     if (tokens.size() < 3)
//     {
//         c->setReplyBuffer(ERR_NOTEXTTOSEND(c->getNickname())); // Error if no message provided
//         return;
//     }

//     // Collect the message from all tokens starting from index 2
//     std::string message;
//     for (size_t i = 2; i < tokens.size(); ++i)
//     {
//         if (i != 2)
//         {
//             message += " ";  // Add space between tokens
//         }
//         message += tokens[i];  // Concatenate the message parts
//     }

//     // Iterate over all targets (separated by commas)
//     std::vector<std::string> targets = split(tokens[1], ',');

//     for (size_t i = 0; i < targets.size(); ++i)
//     {
//         std::string target = targets[i];

//         // If the target is a channel
//         if (target[0] == '#')
//         {
//             // Channel *channel = getChannel(target);  // Get the channel object

//             if (!channel)
//             {
//                 c->setReplyBuffer(ERR_NOSUCHCHANNEL(c->getNickname(), target)); // Error if the channel doesn't exist
//                 continue;  // Move to the next target
//             }
            
//             // Check if the client is part of the channel
//             if (!channel->getClientByFd(c->getFd()))
//             {
//                 c->setReplyBuffer(ERR_NOTONCHANNEL(c->getNickname(), target)); // Error if not a member
//                 continue;
//             }

//             // If the channel has the moderated mode active, check if the user is an operator
//             if (channel->getT() && !channel->getOperatorByFd(c->getFd()))
//             {
//                 c->setReplyBuffer(ERR_CANNOTSENDTOCHAN(c->getNickname(), target)); // Error if not an operator in a moderated channel
//                 continue;
//             }

//             // Send message to all members of the channel
//             std::stringstream ss;
//             ss << c->getNickname() << " PRIVMSG " << target << " :" << message << CRLF;
//             channel->setReplyBufferForAllChannelClients(ss.str());  // Send the message to all channel clients
//         }
//         else  // If the target is a user (nickname)
//         {
//             // Client *recipient = getClientByNick(target); // Find the client by nickname
            
//             // if (!recipient)
//             // {
//             //     c->setReplyBuffer(ERR_NOSUCHNICK(c->getNickname(), target)); // Error if user doesn't exist
//             //     continue;  // Move to the next target
//             // }

//             // // Send the message to the recipient
//             // std::stringstream ss;
//             // ss << c->getNickname() << " PRIVMSG " << target << " :" << message << CRLF;
//             // recipient->addToWriteBuffer(ss.str()); // Send the message to the recipient
//         }
//     }
// }
