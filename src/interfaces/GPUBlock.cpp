//
//  GPUBlock.cpp
//  MWAC_External_Interfaces
//
//  Created by Stephen Ord on 8/12/2015.
//
//

#include "GPUBlock.h"


GPUBlock::GPUBlock() {

    /*! Default constructor for an MWA GPUBlock
     */

    set_sample_size(1);
    //! Default values for the current MWA correlator
    initialise(NULL, 128, 2, 128, 10000);

}

GPUBlock::GPUBlock(char *base) {
    /*! Constructor for a GPUBlock if the memory has already been allocated
     this is likely to be the main constructor
     */
    set_sample_size(1);
    initialise(base,128, 2, 128, 10000);

}
GPUBlock::GPUBlock(const GPUBlock& orig) {

    this->base_ptr = orig.base_ptr;
    this->sample_size = orig.sample_size;
    

}

int GPUBlock::initialise(char *base_ptr, int nstation, int npol, int nchan, int nsteps) {

    /*! Sets the dimensions of the data in this block
     
     The default constructor calls this with the default values for an
     MWA GPUBlock but you can use this to overwrite these default values if 
     this code lives on ...
     */
    set_nstation(nstation);

    set_npol(npol);

    set_nchan(nchan);

    set_nsteps(nsteps);

    //! sets the base address of the data for this block

    this->base_ptr = base_ptr;

    return 1;
}

char * GPUBlock::get_base_addr() {

    return this->base_ptr;

}

char * GPUBlock::get_dat_ptr(int antenna, int pol, int chan, int step) {

    /*! Get a pointer to an individual sample

     Data ordering for input vectors is (running from slowest to fastest)
     [time][channel][station][polarization][complexity]

    */

    return NULL;
}


GPUBlock::~GPUBlock() {

    
}