/** 
 * @file:   ConnectionHandler.cpp
 * @author: Stephen Ord
 * 
 * @date Created on 22 July 2015, 10:32 PM
 * @brief: Simple class to act as a daemon and handle incoming connections
 * 
 * The connection handler is launched by the MWAC correlator and listens on 
 * a socket for incoming connections. 
 * 
 * It passes the data onto an interface which places the data into correlator 
 * memory and manages synchronisation
 *  
 * 
 */

#include "ConnectionHandler.h"


ConnectionHandler::ConnectionHandler() {
}

ConnectionHandler::ConnectionHandler(const ConnectionHandler& orig) {
}

ConnectionHandler::~ConnectionHandler() {
}

