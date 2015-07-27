/* 
 * @file:   ConnectionHandler.h
 * @author: Stephen Ord
 * @date 22 July 2015, 10:32 PM
 * 
 * @brief: Simple class to act as a daemon and handle incoming connections
 * 
 * The connection handler is launched by the MWAC correlator and listens on 
 * a socket for incoming connections. 
 * 
 * It passes the data onto an interface which places the data into correlator 
 * memory and manages synchronisation
 *  
 */

#ifndef CONNECTIONHANDLER_H
#define	CONNECTIONHANDLER_H

#define DEFAULT PORT 8001

class ConnectionHandler {
public:
    ConnectionHandler();
    ConnectionHandler(const ConnectionHandler& orig);
    virtual ~ConnectionHandler();
private:

};

#endif	/* CONNECTIONHANDLER_H */

