#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>
#include <bitset>
#include <unordered_map>

#define ull unsigned long long

using namespace std;
using namespace std::chrono;

int main(){
    auto start = high_resolution_clock::now();
    vector<ull> alph;
    vector<ull> mem{};
    ifstream in;
    in.open("Day15.txt");
    bool find;
    string input;
    while (!in.eof()){
        getline(in,input,',');
        alph.push_back(atoi(input.c_str()));
    }

    // Part 1,2
    unordered_map<ull,int> m;

    for (int i = 0 ; i< alph.size() ; i++){
        m[alph[i]] = i;
    }

    while (alph.size() != 30000000){
        int speak;
        ull last = alph[alph.size()-1];
        if (m.find(last) != m.end()){
            speak = alph.size()-1-(m.find(last)->second);
        }
        else{
            speak = 0;
        }
        m[last] = alph.size()-1;
        alph.push_back(speak);
        if (alph.size() == 2020)
            cout << "Part 1 : " << alph[alph.size()-1] << endl;
    }

    cout << "Part 2 : " << alph[alph.size()-1] << endl;

    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl; 
}
