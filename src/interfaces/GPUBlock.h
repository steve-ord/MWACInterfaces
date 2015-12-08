//
//  GPUBlock.h
//  MWAC_External_Interfaces
//
//  Created by Stephen Ord on 8/12/2015.
//
//

#ifndef __MWAC_External_Interfaces__GPUBlock__
#define __MWAC_External_Interfaces__GPUBlock__

#include <iostream>

#include "File.h"
#include "GPUBlock.h"

class GPUBlock: public File {

public:
    //! Simple constructor
    GPUBlock();

    //! Simple constructir - memory already allocated
    GPUBlock(char *base_ptr);

    //! Simple copy constructor

    GPUBlock(const GPUBlock& orig);

    //! initialiser
    //! this just brings the default initialise from the base clear here in case you need it
    using File::initialise;
    //! and allows this to overload it without hiding it
    int initialise(char *base_ptr,int nstation, int npol, int nchan, int nsteps);


    char * get_base_addr(void);
    //! just brings the default get_dat_ptr into this scope
    using File::get_dat_ptr;
    char * get_dat_ptr(int station, int pol, int chan, int step);

    //! set the sample size (bytes)
    void set_sample_size(int);
    //! destructor

    ~GPUBlock();

private:

    char * base_ptr;
    int sample_size;
    int natural_to_mwac(int antenna, int pol);
    

};


#endif /* defined(__MWAC_External_Interfaces__GPUBlock__) */
