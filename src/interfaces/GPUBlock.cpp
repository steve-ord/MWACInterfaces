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

    /*! the station in the data based upon the antenna number requested

     We have decided to hide all the various station mappings in one place and this is it
     I am going to take and antenna in "natural order" and map it to the GPUBOX station here and from
     then on forget about it
    */

    /*! there are two steps one is the mod16 antenna mapping that the PFB does
     and the second is the receiver ordering that the receivers do
    */

    int station = natural_to_mwac(antenna,pol);

    size_t step_size = get_nchan() * get_nstation() * get_npol() * 2 * this->sample_size;
    size_t channel_offset = get_nstation() * get_npol() * 2 * this->sample_size;
    size_t station_offset = get_npol() * 2 * this->sample_size;
    size_t offset = step*step_size + chan*channel_offset + station * station_offset;

    return get_base_addr()+offset;
}

int GPUBlock::natural_to_mwac(int antenna, int pol) {
    /*! This function calculates the internal station index from an
     antenna and a pol
     */

    return 0;


   
}

GPUBlock::~GPUBlock() {

    
}
