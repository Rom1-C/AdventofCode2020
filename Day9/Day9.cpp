#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;
using namespace std::chrono;

bool find(vector<unsigned long long> v, int k){
    
    for(int i=k-25;i<k-1;i++){
        for(int j=i+1;j<k;j++){
            if(v[i]+v[j] == v[k])
                return true;
        }
    }
    
    return false;
}


int main(){
    auto start = high_resolution_clock::now();
    ifstream in;
    vector<unsigned long long> alph;
    in.open("Day9.txt");
    unsigned long long tmp;
    unsigned long long result;
    result = 0;
    while (!in.eof()){
        in >> tmp;
        alph.push_back(tmp);
    }

    //Part 1
    for (int m=25 ; m< alph.size();m++){
        if (!find(alph,m)){
            result = alph[m];
            break;
        }
    }

    cout << "Part1 : " << result << endl;

    //Part 2
    int i=0;
    int debut, fin;
    int stack = 0;
    for (int m=25 ; m< alph.size();m++){
        stack =0;
        i=m;
        while (stack <=result){
            stack+=alph[i];
            if (stack == result){
                debut = m;
                fin = i;
                m = alph.size();
                break;
            }
            i++;
        }
    }
    int min=INT_MAX;
    for (int m=debut ; m < fin+1 ; m++){
        if (alph[m]<min)
            min=alph[m];
    }

    int max=0;
    for (int m=debut ; m < fin+1 ; m++){
        if (alph[m]>max)
            max=alph[m];
    }

    cout << "Part2 : " << (max+min)<< endl;

    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl; 

    return 0;
}
