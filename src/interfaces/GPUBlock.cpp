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

GPUBlock::GPUBlock(char *base,time_t utctime) {
    /*! Constructor for a GPUBlock if the memory has already been allocated
     this is likely to be the main constructor
     */
    set_sample_size(1);
    set_time(utctime);
    initialise(base,128, 2, 128, 10000);


}
GPUBlock::GPUBlock(const GPUBlock& orig) {

    this->base_ptr = orig.base_ptr;
    this->sample_size = orig.sample_size;
    this->utctime = orig.utctime;


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

    int input = natural_to_mwac(antenna,pol);

    size_t step_size = get_nchan() * get_nstation() * get_npol() * 2 * this->sample_size;
    size_t channel_offset = get_nstation() * get_npol() * 2 * this->sample_size;
    size_t input_offset = 2*this->sample_size;
    size_t offset = step*step_size + chan*channel_offset + input * input_offset;

    return get_base_addr()+offset;
}

int GPUBlock::natural_to_mwac(int antenna, int pol) const {
    /*! This function calculates the internal (GPU/PFB) station index from an
     antenna and a pol in "natural" order
     */
    //! This gets you the mapping to the antenna number - but we now need the mod 16
    static const int nat_mapping[128] = {
        43,42,41,40,47,46,45,44,
        35,34,33,32,39,38,37,36,
        99,98,97,96,103,102,101,100,
        107,106,105,104,111,110,109,108,
        123,122,121,120,127,126,125,124,
        115,114,113,112,119,118,117,116,
        27,26,25,24,31,30,29,28,
        59,58,57,56,63,62,61,60,
        51,50,49,48,55,54,53,52,
        3,2,1,0,7,6,5,4,
        75,74,73,72,79,78,77,76,
        67,66,65,64,71,70,69,68,
        91,90,89,88,95,94,93,92,
        83,82,81,80,87,86,85,84,
        11,10,9,8,15,14,13,12,
        19,18,17,16,23,22,21,20
    };
    //! this gives you the mapping from an input to an index in the GPUBox station array
    static const int input_internal[256] = {
        0,4,8,12,16,20,24,28,
        32,36,40,44,48,52,56,60,
        1,5,9,13,17,21,25,29,
        33,37,41,45,49,53,57,61,
        2,6,10,14,18,22,26,30,
        34,38,42,46,50,54,58,62,
        3,7,11,15,19,23,27,31,
        35,39,43,47,51,55,59,63,
        64,68,72,76,80,84,88,92,
        96,100,104,108,112,116,120,124,
        65,69,73,77,81,85,89,93,
        97,101,105,109,113,117,121,125,
        66,70,74,78,82,86,90,94,
        98,102,106,110,114,118,122,126,
        67,71,75,79,83,87,91,95,
        99,103,107,111,115,119,123,127,
        128,132,136,140,144,148,152,156,
        160,164,168,172,176,180,184,188,
        129,133,137,141,145,149,153,157,
        161,165,169,173,177,181,185,189,
        130,134,138,142,146,150,154,158,
        162,166,170,174,178,182,186,190,
        131,135,139,143,147,151,155,159,
        163,167,171,175,179,183,187,191,
        192,196,200,204,208,212,216,220,
        224,228,232,236,240,244,248,252,
        193,197,201,205,209,213,217,221,
        225,229,233,237,241,245,249,253,
        194,198,202,206,210,214,218,222,
        226,230,234,238,242,246,250,254,
        195,199,203,207,211,215,219,223,
        227,231,235,239,243,247,251,255

    };

    //! what is my station number
    int station = nat_mapping[antenna];
    int input_number = station*get_npol() + pol;


    return input_internal[input_number];


   
}
void GPUBlock::set_time(time_t the_time) {
    this->utctime = the_time;
}
time_t GPUBlock::get_time() const {
    return this->utctime;
}
GPUBlock::~GPUBlock() {

    
}
