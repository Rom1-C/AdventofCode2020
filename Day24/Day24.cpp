#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>

#define ull unsigned long long

using namespace std;
using namespace std::chrono;

int main() {
	auto start = high_resolution_clock::now();
    set<tuple<int,int,int>> grid;
    vector<string> alph;
    vector<tuple<int,int,int>> dir = {{1,-1,0},{0,-1,1},{-1,0,1},{-1,1,0},{0,1,-1},{1,0,-1}};
    ifstream in;
    in.open("Day24.txt");
    ull result = 0;
    string input;
    while (!in.eof()){
        getline(in,input);
        alph.push_back(input);
    }

    //Part1
    for (auto v : alph){
        string line = v;
        tuple<int,int,int> t;
        get<0>(t) = 0;
        get<1>(t) = 0;
        get<2>(t) = 0;

        while (!line.empty()){
            if (line[0] == 'e'){
                get<0>(t) ++;
                get<1>(t) --;
                line = line.substr(1,line.length());
            }
            else if (line[0] == 'w'){
                get<0>(t) --;
                get<1>(t) ++;
                line = line.substr(1,line.length());
            }
            else if (line[0] == 'n' && line[1] == 'w'){
                get<1>(t) ++;
                get<2>(t) --;
                line = line.substr(2,line.length());
            }
            else if (line[0] == 'n' && line[1] == 'e'){
                get<0>(t) ++;
                get<2>(t) --;
                line = line.substr(2,line.length());
            }
            else if (line[0] == 's' && line[1] == 'w'){
                get<0>(t) --;
                get<2>(t) ++;
                line = line.substr(2,line.length());
            }
            else if (line[0] == 's' && line[1] == 'e'){
                get<1>(t) --;
                get<2>(t) ++;
                line = line.substr(2,line.length());
            }
            else{
                cout << "Error : " << line << endl;
            }
        }
        if (grid.count(t) > 0){
            grid.erase(find(grid.begin(),grid.end(),t));
        }
        else{
            grid.insert(t);
        }
    }

    cout << "Part 1 : " << grid.size() << endl;

    //Part2
    int i,j,k,x,y,z;
    for (int m = 0 ; m < 100 ; m++){
        set<tuple<int,int,int>> tmp;
        set<tuple<int,int,int>> check;
        for (auto v : grid){
            tie(i,j,k) = v;
            check.insert(v);
            for (auto m : dir){
                tie(x,y,z) = m;
                check.insert({i+x,j+y,k+z});
            }
        }
        
        for (auto v : check){
            tie(i,j,k) = v;
            int count = 0;
            for (auto c : dir){
                tie(x,y,z) = c;
                if (grid.count({i+x,j+y,k+z})>0)
                    count ++;
            }

            if (grid.count(v) == 0 && count == 2){
                tmp.insert({i,j,k});
            }
            if (grid.count(v) >0 && count == 1 || count == 2){
                tmp.insert({i,j,k});
            }
        }

        grid = tmp;
    }

    cout << "Part 2 : " << grid.size() << endl;

	auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time taken by program: "
         << duration.count() << " microseconds" << endl;
}
