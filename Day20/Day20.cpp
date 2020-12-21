#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <regex>

#define ull unsigned long long

using namespace std;
using namespace std::chrono;
vector<vector<string>> alph;

vector<string> split(const string& str, const string& delim){
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

int main(){
    auto start = high_resolution_clock::now();
    vector<int> tilesId;
    ifstream in;
    in.open("Day20.txt");
    ull result = 1;
    string input;
    while (!in.eof()){
        getline(in,input);
        if (!input.empty()){
            tilesId.push_back(atoi(split(input," ")[1].substr(0,4).c_str()));
            vector<string> tmp;
            for (int i = 0 ; i <10 ; i++){
                getline(in,input);
                tmp.push_back(input);
            }
            alph.push_back(tmp);
        }
    }

    int tab[144][4];
    for (int i = 0 ; i < 144 ; i++){
        for (int j = 0 ; j<4 ; j++){
            tab[i][j] = 0;
        }
    }
    for (int i = 0 ; i< 144 ; i++){
        for (int j = 0 ; j < 144 ; j++){
            int count = 0;
            if (i==j)
                continue;
            string tmp = alph[j][0];
            reverse(tmp.begin(),tmp.end());
            string tmp2 = alph[j][9];
            reverse(tmp2.begin(),tmp2.end());
            if (alph[i][0] == alph[j][9] || alph[i][0] == alph[j][0] || alph[i][0] == tmp || alph[i][0] == tmp2){ //Top
                tab[i][0] ++;
            }
            for (int m = 0 ; m < 10 ; m++){
                if (alph[i][0][m] == alph[j][m][9]){
                    count ++;
                }
            }
            if (count >=10)
                tab[i][0] ++;
            count = 0;
            for (int m = 0 ; m < 10 ; m++){
                if (alph[i][0][m] == alph[j][9-m][9]){
                    count ++;
                }
            }
            if (count >=10)
                tab[i][0] ++;
            count = 0;
            for (int m = 0 ; m < 10 ; m++){
                if (alph[i][0][m] == alph[j][m][0]){
                    count ++;
                }
            }
            if (count >=10)
                tab[i][0] ++;
            count = 0;
            for (int m = 0 ; m < 10 ; m++){
                if (alph[i][0][m] == alph[j][9-m][0]){
                    count ++;
                }
            }
            if (count >=10)
                tab[i][0] ++;
            count = 0;
            if (alph[i][9] == alph[j][9] || alph[i][9] == alph[j][0] || alph[i][9] == tmp || alph[i][9] == tmp2){ //Bottom
                tab[i][1] ++;
            }
            for (int m = 0 ; m < 10 ; m++){
                if (alph[i][9][m] == alph[j][m][9]){
                    count ++;
                }
            }
            if (count >=10)
                tab[i][1] ++;
            count = 0;
            for (int m = 0 ; m < 10 ; m++){
                if (alph[i][9][m] == alph[j][9-m][9]){
                    count ++;
                }
            }
            if (count >=10)
                tab[i][1] ++;
            count = 0;
            for (int m = 0 ; m < 10 ; m++){
                if (alph[i][9][m] == alph[j][m][0]){
                    count ++;
                }
            }
            if (count >=10)
                tab[i][1] ++;
            count = 0;
            for (int m = 0 ; m < 10 ; m++){
                if (alph[i][9][m] == alph[j][9-m][0]){
                    count ++;
                }
            }
            if (count >=10)
                tab[i][1] ++;
            count = 0;
            for (int m = 0 ; m < 10 ; m++){ //Left
                if (alph[i][m][0] == alph[j][m][9]){ 
                    count++;
                }
            }
            if (count >=10)
                tab[i][2] ++;
            count = 0;
            for (int m = 0 ; m < 10 ; m++){
                if (alph[i][m][0] == alph[j][m][0]){ 
                    count++;
                }
            }
            if (count >=10)
                tab[i][2] ++;
            count = 0;
            for (int m = 0 ; m < 10 ; m++){
                if (alph[i][m][0] == alph[j][0][m]){ 
                    count++;
                }
            }
            if (count >=10)
                tab[i][2] ++;
            count = 0;
            for (int m = 0 ; m < 10 ; m++){
                if (alph[i][m][0] == alph[j][9][m]){ 
                    count++;
                }
            }
            if (count >=10)
                tab[i][2] ++;
            count = 0;
            for (int m = 0 ; m < 10 ; m++){
                if (alph[i][m][0] == alph[j][9-m][9]){ 
                    count++;
                }
            }
            if (count >=10)
                tab[i][2] ++;
            count = 0;
            for (int m = 0 ; m < 10 ; m++){
                if (alph[i][m][0] == alph[j][9-m][0]){ 
                    count++;
                }
            }
            if (count >=10)
                tab[i][2] ++;
            count = 0;
            for (int m = 0 ; m < 10 ; m++){
                if (alph[i][m][0] == alph[j][0][9-m]){ 
                    count++;
                }
            }
            if (count >=10)
                tab[i][2] ++;
            count = 0;
            for (int m = 0 ; m < 10 ; m++){
                if (alph[i][m][0] == alph[j][9][9-m]){ 
                    count++;
                }
            }
            if (count >=10)
                tab[i][2] ++;
            count = 0;
            for (int m = 0 ; m < 10 ; m++){
                if (alph[i][m][9] == alph[j][m][9]){ 
                    count ++;
                }
            }
            if (count >=10)
                tab[i][3] ++;
            count = 0;
            for (int m = 0 ; m < 10 ; m++){
                if (alph[i][m][9] == alph[j][m][0]){ 
                    count ++;
                }
            }
            if (count >=10)
                tab[i][3] ++;
            count = 0;
            for (int m = 0 ; m < 10 ; m++){
                if (alph[i][m][9] == alph[j][0][m]){ 
                    count ++;
                }
            }
            if (count >=10)
                tab[i][3] ++;
            count = 0;
            for (int m = 0 ; m < 10 ; m++){
                if (alph[i][m][9] == alph[j][9][m]){ 
                    count ++;
                }
            }
            if (count >=10)
                tab[i][3] ++;
            count = 0;
            for (int m = 0 ; m < 10 ; m++){
                if (alph[i][m][9] == alph[j][9-m][9]){ 
                    count ++;
                }
            }
            if (count >=10)
                tab[i][3] ++;
            count = 0;
            for (int m = 0 ; m < 10 ; m++){
                if (alph[i][m][9] == alph[j][9-m][0]){ 
                    count ++;
                }
            }
            if (count >=10)
                tab[i][3] ++;
            count = 0;
            for (int m = 0 ; m < 10 ; m++){
                if (alph[i][m][9] == alph[j][0][9-m]){ 
                    count ++;
                }
            }
            if (count >=10)
                tab[i][3] ++;
            count = 0;
            for (int m = 0 ; m < 10 ; m++){
                if (alph[i][m][9] == alph[j][9][9-m]){ 
                    count ++;
                }
            }
            if (count >=10)
                tab[i][3] ++;
            count = 0;
            
        }
    }

    for (int i = 0 ; i<144 ; i++){
        if (tab[i][0] == 0 && tab[i][2] == 0){
            result*=tilesId[i];
        }
        if (tab[i][0] == 0 && tab[i][3] == 0){
            result*=tilesId[i];
        }
        if (tab[i][1] == 0 && tab[i][2] == 0){
            result*=tilesId[i];
        }
        if (tab[i][1] == 0 && tab[i][3] == 0){
            result*=tilesId[i];
        }
    }

    cout << result << endl;

    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl; 
}
