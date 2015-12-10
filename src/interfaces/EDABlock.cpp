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
#include <string.h>

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

    set_complex_sample_size(2);
    /*! Default values for the current MWA correlator
        Now the eda block deals in inputs ... but the correlator thinks in terms of inputs
     
        so we should floor(ninputs/2) + ninputs%2 for the number of stations
     
     */

    //! set default npol to 2
    set_npol(2);

    //! get nstations

    int nstations = int(eda_block_hdr->n_inp/2) + eda_block_hdr->n_inp%2;


    set_nstation(nstations);

    set_nchan(eda_block_hdr->n_chan);

    set_nsteps(eda_block_hdr->n_times);

    this->block_size = eda_block_hdr->n_inp * eda_block_hdr->n_chan * eda_block_hdr->n_times * get_complex_sample_size();

    this->epoch_time = eda_block_hdr->epoch_time;

    this->utctimes = eda_block_hdr->block_time_offset;

    this->inputs = eda_block_hdr->input_id;



}


EDABlock::EDABlock(const EDABlock& orig) {

    this->base_ptr = orig.base_ptr;
    this->sample_size = orig.sample_size;
    this->utctimes = orig.utctimes;
    this->epoch_time = orig.epoch_time;
    this->sample_size = orig.sample_size;




}

int EDABlock::initialise(char *base_ptr, int nstation, int nchan, int nsteps, int nblocks) {

    /*! Sets the dimensions of the data in this block
     
     The default constructor does not use this - but it is here in case you need
     some thing more specific or maybe want to change the porperties of an instance after
     instatiation.
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
char * EDABlock::get_dat_ptr(int input, int chan, int step) {
    /*! Gets the data of the current block/sample.
     */
    //! base address of the block
    char *base = this->base_ptr + this->current_block * this->block_size;
    //! offset to the step within the block
    size_t offset = (step*this->n_inp*this->get_nchan()*2);
    //! offset to the input
    offset = offset + (input * this->get_nchan() * 2);
    //!
    offset = offset + chan;

    return base+offset;
}
char * EDABlock::get_dat_ptr(int antenna, int pol, int chan, int step) {

    /*! Get a pointer to an individual sample

    */

    int input = antenna * this->get_npol() + pol;


    return get_dat_ptr(input,chan,step);
}

void EDABlock::set_time(time_t the_time) {

    
    int match = 0;
    for (int i = 0;i<this->n_blocks;i++) {
        if (the_time == (time_t) (this->utctimes[i]+this->epoch_time)){
            this->current_block = i;
            match = 1;
            break;
        }
    }
    if (!match){
        throw "No time match\n";
    }

}
int EDABlock::get_input(int index) {
    return this->inputs[index];
}
time_t EDABlock::get_time() const {
    return this->utctimes[this->current_block] + this->epoch_time;
}
EDABlock::~EDABlock() {

    
}
