#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
using namespace std::chrono;

unsigned long long modInverse(unsigned long long a, unsigned long long m) { 
    a = a % m; 
    for (int x = 1; x < m; x++) 
        if ((a * x) % m == 1) 
            return x; 
    return 0;
} 

int main(){
    auto start = high_resolution_clock::now();
    vector<pair<long long,int>> alph;
    ifstream in;
    int result=0;
    long long i=0;
    in.open("Day13.txt");
    string input;
    getline(in, input);
    int m=0;
    int timestamp = atoi(input.c_str());
    while (!in.eof()){
        getline(in,input,',');
        if(input != "x"){
            alph.push_back({atoi(input.c_str()),atoi(input.c_str())-m});
        }
        m++;
    }

    int best = 100;
    int id;
    // Part 1
    for (auto v : alph){
        int j = timestamp/v.first;
        j = (j+1)*v.first;
        if (j-timestamp < best){
            best = j-timestamp;
            id = v.first;
        }
    }

    cout << "Part 1 : " << (best*id) << endl;

    // Part 2 , Chinese remainder theorem
    unsigned long long N = 1;
    for (int i = 0 ; i< alph.size() ; i++){
        N*=alph[i].first;
    }
    unsigned long long x = 0;

    unsigned long long p;
    for (int i=0 ; i < alph.size() ; i++){
        p = N / alph[i].first;
        x += (p*modInverse(p,alph[i].first)*alph[i].second);
    }

    cout << "Part 2 : " << (x%N) << endl;

    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl; 
}
