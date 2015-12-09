//
//  EDABlock.cpp
//  MWAC_External_Interfaces
//
//  Created by Stephen Ord on 8/12/2015.
//
//

#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>

#include "mwa_eda.h"

#include "EDABlock.h"


EDABlock::EDABlock() {

    /*! Default constructor for an MWA EDABlock
     This is a shared memory block that contains several seconds worth of data from
     a handful of antennas in the EDA and LFAA(AAVS) arrays
     
     The main difference here is that each block contains more than 1 second ...

     */

    key_t mwa_key = atoi(MWA_EDA_SHM_NAME);
    void *ptr = shmat(mwa_key,NULL,SHM_RDONLY);
    if (ptr == (void *)-1) {
       throw "EDABlock::default constructor failed to attach\n";
    }
    //! declare the shm header pointer
    mwa_eda_shmbuf_header *eda_block_hdr = NULL;
    //! assign from the shm block

    eda_block_hdr = (mwa_eda_shmbuf_header *) ptr;

    char *base_ptr = (char *) ptr;
    //! add the header
    base_ptr += 4096;

    set_sample_size(1);
    /*! Default values for the current MWA correlator
        Now the eda block deals in inputs ... but the correlator thinks in terms of inputs
     
        so we should floor(ninputs/2) + ninputs%2 for the number of stations
     
     */

    //! set default npol to 2
    set_npol(2);

    //! get nstations

    int nstations = int(eda_block_hdr->n_inp/2) + eda_block_hdr->n_inp%2;
    initialise(base_ptr, nstations, eda_block_hdr->n_chan,eda_block_hdr->n_times,eda_block_hdr->n_blocks);
}


EDABlock::EDABlock(const EDABlock& orig) {

    this->base_ptr = orig.base_ptr;
    this->sample_size = orig.sample_size;
    this->utctime = orig.utctime;


}

int EDABlock::initialise(char *base_ptr, int nstation, int nchan, int nsteps, int nblocks) {

    /*! Sets the dimensions of the data in this block
     
     The default constructor calls this with the default values for an
     MWA EDABlock but you can use this to overwrite these default values if 
     this code lives on ...
     */
    set_nstation(nstation);

    set_nchan(nchan);

    set_nsteps(nsteps);

    //! sets the base address of the data for this block

    this->base_ptr = base_ptr;

    /*! now we have some interesting timing information and pointers to set up as we
     have more than 1 second in the data
     */

    return 1;
}

char * EDABlock::get_base_addr() {

    return this->base_ptr;

}

char * EDABlock::get_dat_ptr(int antenna, int pol, int chan, int step) {

    /*! Get a pointer to an individual sample

    */

    size_t offset = 0;
    
    return get_base_addr()+offset;
}

void EDABlock::set_time(time_t the_time) {
    this->utctime = the_time;
}
time_t EDABlock::get_time() const {
    return this->utctime;
}
EDABlock::~EDABlock() {

    
}
