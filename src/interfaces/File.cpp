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

}

File::File(const File& orig) {
}

File::~File() {
}

void File::set_nchan(int nchan) {
    this->nchan = nchan;
}

int File::get_nchan() {
    return this->nchan;
}

void File::set_nstation(int nstation) {
    this->nstation = nchan;
}

int File::get_nstation() {
    return this->nstation;
}
void File::set_npol(int npol) {
    this->npol = npol;
}

int File::get_npol() {
    return this->npol;
}

int File::get_nsteps() {
    return this->nsteps;
}

