#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
using namespace std::chrono;

int main(){
    auto start = high_resolution_clock::now();
    vector<pair<char,int>> alph;
    ifstream in;
    in.open("Day12.txt");
    int result = 0;
    char dir[] = {'N','E','S','W'};
    int x = 0;
    int y = 0;
    int face = 1;
    string input;
    while (!in.eof()){
        getline(in,input);
        alph.push_back({input.substr(0,1)[0], atoi(input.substr(1,input.length()).c_str())});
    }

    // Part 1
    for (int i=0 ; i < alph.size(); i++){
        if (alph[i].first == 'F'){
            if (dir[face] == 'E')
                x+=alph[i].second;
            else if (dir[face] == 'S')
                y-=alph[i].second;
            else if (dir[face] == 'W')
                x-=alph[i].second;
            else{
                y+=alph[i].second;
            }
        }
        else if (alph[i].first == 'L'){
            face = (face+((360-alph[i].second)/90))%4;
        }
        else if (alph[i].first == 'R'){
            face = (face+(alph[i].second/90))%4;
        }
        else if (alph[i].first == 'E'){
            x+=alph[i].second;
        }
        else if (alph[i].first == 'S'){
            y-=alph[i].second;
        }
        else if (alph[i].first == 'W'){
            x-=alph[i].second;
        }
        else {
            y+=alph[i].second;
        }
    }
    std::cout << "Part 1 : " << (abs(x)+abs(y)) << endl;

    //Part 2
    int waypoint[] = {10,1};
    face = 1;
    x = 0;
    y = 0;

    for (int i=0 ; i < alph.size(); i++){
        if (alph[i].first == 'F'){
            x+=waypoint[0]*alph[i].second;
            y+=waypoint[1]*alph[i].second;
        }
        else if (alph[i].first == 'L'){
            if (alph[i].second == 90){
                int tmp = waypoint[0];
                waypoint[0] = -waypoint[1];
                waypoint[1] = tmp;
            }
            if (alph[i].second == 180){
                waypoint[0] = -waypoint[0];
                waypoint[1] = -waypoint[1];
            }
            
            if (alph[i].second == 270){
                int tmp = waypoint[0];
                waypoint[0] = waypoint[1];
                waypoint[1] = -tmp;
            }
        }
        else if (alph[i].first == 'R'){
            if (alph[i].second == 90){
                int tmp = waypoint[0];
                waypoint[0] = waypoint[1];
                waypoint[1] = -tmp;
            }
            if (alph[i].second == 180){
                waypoint[0] = -waypoint[0];
                waypoint[1] = -waypoint[1];
            }
            if (alph[i].second == 270){
                int tmp = waypoint[0];
                waypoint[0] = -waypoint[1];
                waypoint[1] = tmp;
            }
        }
        else if (alph[i].first == 'E'){
            waypoint[0]+=alph[i].second;
        }
        else if (alph[i].first == 'S'){
            waypoint[1]-=alph[i].second;
        }
        else if (alph[i].first == 'W'){
            waypoint[0]-=alph[i].second;
        }
        else {
            waypoint[1]+=alph[i].second;
        }
    }

    cout << "Part 2 : " << (abs(x) + abs(y)) << endl;

    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl; 
}
