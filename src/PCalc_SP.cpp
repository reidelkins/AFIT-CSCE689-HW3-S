//SWITCHED FROM CMATH TO MATH.H BECAUSE OF MAC OS
//#include <cmath>
#include <math.h>

#include <PCalc_SP.h>

PCalc_SP::PCalc_SP(unsigned int array_size):PCalc(array_size) {

}

void PCalc_SP::markNonPrimes() {

    //in the first50kprimes.txt file it has 0 
    //and 1 included, so I comment them out here
    // this->at(0) = false;
    // this->at(1) = false;

    //Use the Sieve of Eratothenes Formula, information for it found at
    //https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes 
    for(int i = 2; i < sqrt(this->array_size()); i++) {
        if(this->at(i)) {
            for(int j = pow(i, 2); j < this->array_size(); j = j+i) {
                this->at(j) = false;
            }
        }
    }


}
