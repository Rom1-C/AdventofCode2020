#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <string>
#include <fstream>

using namespace std;
using namespace std::chrono;

int countChar(string s, char c) {
  int count = 0;

  for (int i = 0; i < s.size(); i++)
    if (s.at(i) == c) 
        count++;

  return count;
}

int main(){
    auto start = high_resolution_clock::now();
    ifstream in;
    in.open("Day2.txt");
    string input[1000][4];
    string tmp;
    int first,second,third, resultat;
    int i=0;
    while (i<1000){
        in >> tmp;
        first = tmp.find('-');
        input[i][0] = tmp.substr(0,first);
        input[i][1] = tmp.substr(first+1,tmp.length());
        in >> tmp;
        input[i][2] = tmp.substr(0,1);
        in >> tmp;
        input[i][3] = tmp;
        i++;
    }

    resultat = 0;
    // Part 1
    for (int j=0 ;  j <1000 ; j++){
        int a = stoi(input[j][0]);
        int b = stoi(input[j][1]);
        int count = countChar(input[j][3], (input[j][2].c_str())[0]);
        if (count >= a && count <= b){
            resultat ++;
        }
    }

    cout << "Part 1 : " << resultat << endl;
    
    //Part 2
    resultat = 0;
    for (int j=0 ;  j <1000 ; j++){
        int a = stoi(input[j][0]);
        int b = stoi(input[j][1]);
        if (input[j][3].at(a-1) == (input[j][2].c_str())[0] && input[j][3].at(b-1) != (input[j][2].c_str())[0]){
            resultat ++;
        }
        if (input[j][3].at(a-1) != (input[j][2].c_str())[0] && input[j][3].at(b-1) == (input[j][2].c_str())[0]){
            resultat ++;
        }
    }

    cout << "Part 2 : " << resultat << endl;

    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl; 

    return 0;
}
