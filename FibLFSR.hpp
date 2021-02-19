#ifndef _LFSR_H_
#define _LFSR_H_

#include <iostream>
#include <string>

class FibLFSR
{

public:
   
    FibLFSR(std::string seed, int t);
    int step();
    int generate(int n);

    friend std::ostream& operator<< (std::ostream &out, const FibLFSR &lfsr);

private:
   
    std::string seed;
    int tap;

};


#endif
