#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include <math.h>
#include <map>

#define ull unsigned long long

using namespace std;
using namespace std::chrono;

ull modulo(ull a, ull b, ull n){
    long long x=1, y=a; 
    while (b > 0) {
        if (b%2 == 1) {
            x = (x*y) % n;
        }
        y = (y*y) % n;
        b = b >> 1;
    }
    return x % n;
}

int main() {
	auto start = high_resolution_clock::now();
    ull x;
    ull y;
    ifstream in;
    in.open("Day25.txt");
    string input;
    getline(in,input);
    x = atoi(input.c_str());
    getline(in,input);
    y = atoi(input.c_str());
    map<ull,ull> alph;
    ull m = ceil(sqrt(20201227));
    ull result;
    for (int i = 0 ; i < m ; i++){
        alph.insert({modulo(7,i,20201227),i});
    }
    for (int i = 0 ; i < m ; i++){
        alph[modulo(7,i,20201227)] = i;
    }
    ull inv = modulo(7,20201225*m,20201227);
    ull res=0;
    for (int i = 0 ; i < m ; i++){
        ull y = (x * modulo(inv,i,20201227))%20201227;
        auto it = alph.find(y);
        if (it!=alph.end()){
            res = i*m + it->second;
            break;
        }
    }

    result = modulo(y,res,20201227);
	auto stop = high_resolution_clock::now(); 

    cout << "Day 25 : " << result << endl;

    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time taken by program: "
         << duration.count() << " microseconds" << endl;

    return 0;
}
