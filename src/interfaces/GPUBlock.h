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


    //! Simple copy constructor

    GPUBlock(const GPUBlock& orig);

    //! initialiser

    int initialise(void);
    //! destructor
    ~GPUBlock();

};


#endif /* defined(__MWAC_External_Interfaces__GPUBlock__) */
