//
//  mwa_eda.h
//
//
//  Created by Randall Wayth
//
//  Added to External Interfaces Stephen Ord on 8/12/2015.
//
//

#ifndef _MWA_EDA_H__
#define _MWA_EDA_H__

#include <semaphore.h>
#include <time.h>

#define MWA_EDA_SHM_NAME    "mwa_eda"
#define MWA_EDA_SHM_N_BLOCKS 10
#define MWA_EDA_MAX_INPUTS 8

enum mwa_eda_datatypes {COMPLEX_INT8_8=1};

/* shared mem data block is a single contiguous memory block consisting of:
 - 1 page (4096 bytes) of the header data structure below, then
 - n_blocks blocks of data, each of size block_size bytes
 - within each block, there are n_inp sections, one for each antenna "input" (i.e. pol)
 each of which is n_chan*n_times*bytes/sample bytes long (determined by datatype)
 channels vary most quickly
 */
typedef struct {
    int n_inp;      // number of independent inputs
    int n_times;    // number of time samples per block per input
    int n_chan;     // number of channels per time sample per block per input
    int n_blocks;   // number of blocks in buffer
    int block_size;
    int datatype;   // described by enumerated type above
    float chan_bw;  // channel bandwidth in Hz
    time_t epoch_time;  // reference time which blocks are releative to. Doesn't change
    volatile int newest_buf;
    sem_t sem;
    volatile int block_time_offset[MWA_EDA_SHM_N_BLOCKS];    // time offset (seconds) for the block relative to epoch_time
    int input_id[MWA_EDA_MAX_INPUTS];    // time offset (seconds) for the block relative to epoch_time
} mwa_eda_shmbuf_header;

#endif
