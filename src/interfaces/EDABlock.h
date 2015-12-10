//
//  EDABlock.h
//  MWAC_External_Interfaces
//
//  Created by Stephen Ord on 8/12/2015.
//
//

#ifndef __MWAC_External_Interfaces__EDABlock__
#define __MWAC_External_Interfaces__EDABlock__

#include <iostream>
#include <time.h>

#include "File.h"
#include "mwa_eda.h"

class EDABlock: public File {

    //! Simple constructor uses the default eda parameters
    EDABlock();

    //! Simple copy constructor

    EDABlock(const EDABlock& orig);

    //! initialiser
    //! this just brings the default initialise from the base clear here in case you need it
    using File::initialise;
    //! and allows this to overload it without hiding it
    int initialise(char *base_ptr,int nstation, int npol, int nchan, int nsteps);


    char * get_base_addr(void);
    //! just brings the default get_dat_ptr into this scope
    using File::get_dat_ptr;
    char * get_dat_ptr(int station, int pol, int chan, int step);
    char * get_dat_ptr(int input, int chan,int step);
    
    //! set the sample size (bytes)
    void set_complex_sample_size(int);

    //! match ... sets the current block to that requested - if it exists in the list
    void set_time(time_t utctime);

    //! get the time
    time_t get_time() const;

    //! get the input id
    int get_input(int index) const;
    
    //! destructor

    ~EDABlock();

private:
    //! The pointer to first sample
    char * base_ptr;
    //! the size of a sample in bytes
    time_t epoch_time;
    //! utctimes of all the blocks
    volatile int *utctimes;
    //! the number of blocks
    int n_blocks;
    //! current block being used
    int current_block;
    //! Inputs in these blocks
    int n_inp;
    //! array of inputs
    int *inputs;
    //! size of a block
    size_t block_size;
};


#endif /* defined(__MWAC_External_Interfaces__EDABlock__) */
