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

#include <time.h>

class File {
public:
    //! Simple constructor
    File();
    //! Simple destructor
    File(const File& orig);
    //! pure virtual initialiser


    virtual int initialise(void) = 0;
    //! destructor

    //! Set the number of channels in this file
    void set_nchan(int nchan);
    //! Get the number of channels in this file
    int get_nchan(void) const;

    //! Set the number of stations in this file
    void set_nstation(int nstation);

    //! Get the number of stations in this file
    int get_nstation(void) const;

    //! Get the number of polarisations
    void set_npol(int npol);
    //! Set the number of polarisations
    int get_npol(void) const;

    //! Get the number of time steps in the file
    int get_nsteps(void) const;

    //! Set the number of time steps in the file
    void set_nsteps(int nstep);

    //! The time label of this frame
    virtual void set_time(time_t the_time) = 0;

    //! Get the time
    virtual time_t get_time() const = 0;

    //! Get the base address of the data block
    virtual char * get_base_addr(void) = 0;

    //! Get the pointer for a particular sample
    virtual char * get_dat_ptr(void) = 0;

  

    //! Destructor
    virtual ~File();
private:
    //! the number of stations in this file
    int nstation;

    //! the number of polarisations per station
    int npol;

    //! the number of channels per polarisation
    int nchan;

    //! the number of time steps
    int nsteps;



};

#endif	/* FILE_H */

