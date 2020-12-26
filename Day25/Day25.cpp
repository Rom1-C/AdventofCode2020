#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <fstream>
#include <string>

#define ull unsigned long long

using namespace std;
using namespace std::chrono;

int main() {
	auto start = high_resolution_clock::now();
    int x;
    int y;
    ifstream in;
    in.open("Day25.txt");
    string input;
    getline(in,input);
    x = atoi(input.c_str());
    getline(in,input);
    y = atoi(input.c_str());
    ull value = 1;
    ull result = 1;
    while (value != x){
        value*=7;
        value%=20201227;
        result*=y;
        result%=20201227;
    }

    cout << "Day 25 : " << result << endl;
    

	auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time taken by program: "
         << duration.count() << " microseconds" << endl;
}
