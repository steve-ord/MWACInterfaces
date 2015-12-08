/** 
 * @file:   File.h
 * @author: Stephen Ord
 * @brief Abstract base class for files used as interfaces to the MWA Correlator 
 * @date 22 July 2015, 9:33 PM
 * 
 * This library may support multiple interfaces that I am essentially thinking of 
 * as "files" though they are likely to be mostly socket connections.
 * Keeping the interface file based may allow some extension and generalisation
 * outside the MWA.
 * 
 */

#ifndef FILE_H
#define	FILE_H

class File {
public:
    //! Simple constructor
    File();
    //! Simple destructor
    File(const File& orig);
    //! pure virtual initialiser

    virtual int initialise(void) = 0;
    //! destructor
    virtual ~File();
private:

};

#endif	/* FILE_H */

