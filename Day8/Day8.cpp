#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <unordered_set>

using namespace std;
using namespace std::chrono;

int acc = 0;
vector<int> jmps;
vector<int> nops;

bool checkCode(vector<pair<string, int>> v, bool initializeVectors){
    unordered_set<int> m;

    for (int i = 0; i < v.size(); i++){
        if (v[i].first == "acc"){
            if (m.find(i) != m.end()){
                return true;
            }
            m.insert(i);
            acc += v[i].second;
        }
        else if (v[i].first == "jmp"){
            if (m.find(i) != m.end()){
                return true;
            }
            if (initializeVectors){
                jmps.push_back(i);
            }

            m.insert(i);
            i += v[i].second - 1;
        }

        else if (v[i].first == "nop"){
            if (m.find(i) != m.end()){
                return true;
            }
            if (initializeVectors){
                nops.push_back(i);
            }
            m.insert(i);
        }
    }
    return false;
}


int main(){
    auto start = high_resolution_clock::now();
    ifstream in;
    vector<pair<string,int>> alph;
    bool pass[611];
    for (int i = 0 ; i < 611 ; i++)
        pass[i] = false;
    in.open("Day8.txt");
    string tmp;
    int tmpInt,result;
    result = 0;
    int m=0;
    while (!in.eof()){
        in >> tmp;
        in >> tmpInt;
        alph.push_back({tmp,tmpInt});
    }

    //Part 1
    for (int j=0 ; j < alph.size(); j++){
        if (alph[j].first == "jmp"){
            j += alph[j].second-1;
        }
        if (alph[j].first == "acc"){
            result+=alph[j].second;
        }
        if (pass[j]){
            break;
        }
        pass[j] = true;
    }
    
    cout << "Part 1 : " << result << endl;


    //Part 2
    bool find = false;
    checkCode(alph, true); 

    for (int jmp : jmps){
        alph[jmp].first = "nop";
        acc = 0;
        bool infinite = checkCode(alph, false);
        if (!infinite){
            find = true;
            break;
        }
        alph[jmp].first ="jmp";
    }

    if (!find)
    {
        for (int nop : nops)
        {
            acc = 0;
            alph[nop].first = "jmp";
            bool infinite = checkCode(alph, false);
            if (!infinite){
                break;
            }
            alph[nop].first ="nop";
        }
    }
       
    
    cout << "Part 2 : " <<acc << endl;


    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl; 

    return 0;
}
