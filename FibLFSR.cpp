#include "FibLFSR.hpp"

FibLFSR::FibLFSR(std::string seed, int t) : seed(seed), tap(t){}

int FibLFSR::step(){
    int size = seed.size();

    int tvalue = seed[size-1 - tap] - '0';
    int leftvalue = seed[0] - '0';
    int v = tvalue ^ leftvalue;
    seed = seed.substr(1,size-1) + std::to_string(v);
    return v;
}

int FibLFSR::generate(int n){
    int ans = 0;
    
    for(int i = 0; i < n; i++){
        ans = ans << 1 | step();
    }
    
    return ans;
}

std::ostream &operator<<(std::ostream &out, const FibLFSR &lfsr){
    out << lfsr.seed;
    return out;
}


