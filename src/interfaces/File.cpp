/* 
 * File:   File.cpp
 * Author: sord
 * 
 * Created on 22 July 2015, 9:33 PM
 */

#include "File.h"

File::File() {

    //! default init

    nstation = 0;
    nchan = 0;
    npol = 0;
    nsteps = 0;
    complex_sample_size = 0;

}

File::File(const File& orig) {

    this->nstation = orig.nstation;
    this->nchan = orig.nchan;
    this->npol = orig.npol;
    this->nsteps = orig.nsteps;
    this->complex_sample_size = orig.complex_sample_size;

}

File::~File() {
}

void File::set_complex_sample_size(int sz){
    this->complex_sample_size = sz;
}
size_t File::get_complex_sample_size(void) const {
    return this->complex_sample_size;
}
void File::set_nchan(int nchan) {
    this->nchan = nchan;
}

int File::get_nchan() const {
    return this->nchan;
}

void File::set_nstation(int nstation) {
    this->nstation = nchan;
}

int File::get_nstation() const {
    return this->nstation;
}
void File::set_npol(int npol) {
    this->npol = npol;
}

int File::get_npol()  const {
    return this->npol;
}

int File::get_nsteps() const {
    return this->nsteps;
}

