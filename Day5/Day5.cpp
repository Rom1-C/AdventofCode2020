#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <string>
#include <fstream>

using namespace std;
using namespace std::chrono;

int main(){
    auto start = high_resolution_clock::now();
    ifstream in;
    char c;
    in.open("Day5.txt");
    string tmp;
    int row[2], column[2], id;
    int ids[128*8+7];
    for (int i = 0 ; i <128*8+7;i++){
        ids[i] = 0;
    }
    row[0] = 0;
    row[1] = 127;
    id = 0;
    column[0] = 0;
    column[1] = 7;
    while (!in.eof()){
        row[0] = 0;
        row[1] = 127;
        column[0] = 0;
        column[1] = 7;
        in >> tmp;
        for (int i = 0 ; i< 7 ; i++){
            if (tmp.c_str()[i] == 'F'){
                row[1] = (row[0]+row[1])/2;
            }
            else{
                row[0] = (row[0]+row[1]+1)/2;
            }
        }

        for (int i = 7 ; i< 10 ; i++){
            if (tmp.c_str()[i] == 'L'){
                column[1] = (column[0]+column[1])/2;
            }
            else{
                column[0] = (column[0]+column[1]+1)/2;
            }
        }

        ids [row[0]*8+column[0]] = 1;
        if (row[0]*8+column[0] > id)
            id = row[0]*8+column[0];
    }

    cout << "Part 1 : " << id << endl;

    //Part 2
    for (int k = 50 ; k < id ; k++){
        if (ids[k]!=1){
            cout << "Part 2 : " << k << endl;
            break;
        }
    }


    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl; 

    return 0;
}
