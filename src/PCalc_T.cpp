//SWITCHED FROM CMATH TO MATH.H BECAUSE OF MAC OS
//#include<cmath>
#include <math.h>
#include <thread>
#include <mutex>
#include <vector>
#include <iostream>

#include <PCalc_T.h>


PCalc_T::PCalc_T(unsigned int array_size, unsigned int threads):PCalc(array_size) {
    this->numThreads = threads;
    //creates a mutex semaphore for each element in our number array
    //so that element can be locked if it needs to be overwritten
    mtx = std::vector<std::mutex> (array_size);
    
}


void PCalc_T::markNonPrimes() {
    
    for(int i = 2; i < sqrt(this->array_size()); i++) {
        if(this->at(i)) {
            //creates the max number of threads, sends them off to do work
            //when they return they join back and if there is more work
            //it continues to loop through this process
            if(this->threadsRunning == this->numThreads) {
                for(int j = 0; j < this->numThreads; j++) {
                    if(vThreads.at(j).joinable()) {
                        vThreads.at(j).join();
                        this->threadsRunning--;
                    }
                }
                vThreads.clear();
            } 
            createThread(i);
            this->threadsRunning++;
            

        }
    }
    //join any threads left
    for(int i = 0; i < vThreads.size(); i++) {
        if(vThreads.at(i).joinable())
            vThreads.at(i).join();
    }
}

void PCalc_T::createThread(int i) {
    auto f = [=](int i){primeThread(i);};
    std::thread newThread(f, i);
    vThreads.push_back(std::move(newThread));
}

void PCalc_T::primeThread(int i) {
    for(int j = pow(i, 2); j < this->array_size(); j = j+i) {
        //could possibly be quicker if didn't have this check
        //I do not think so though
        if(this->at(j)) {
            //waits until can lock an element, then changes it and unlocks it
            while(!mtx[i].try_lock());
                this->at(j) = false;
                mtx[i].unlock();
        }           
    }
}

//for i = 2 to sqrt(n), while currentThreads != maxThreads
//create thread, send thread to do job for var i
//thread returns, and joins back
