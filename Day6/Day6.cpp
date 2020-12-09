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
    int alph[26];
    for (int m = 0 ; m<26; m++){
        alph[m] = 0;
    }
    in.open("Day6In.txt");
    string tmp;
    int first,count, result1, result2;
    result1 =0;
    result2 =0;
    int i=0;
    count =0;
    while (!in.eof()){
        in >> tmp;
        i++;
        for (int j = 0 ; j < tmp.length(); j++){
            alph[tmp.c_str()[j]-97] ++;
        }

        if (in.peek()=='\n'){
            in.get(c);
            if (in.peek()=='\n'){
                in.get(c);

                for (int m = 0 ; m<26; m++){
                    if (alph[m] >=i) {
                        count++;
                    }
                    if (alph[m] !=0)
                        result1 ++;
                }
                result2+=count;
                count =0;
                
                for (int m = 0 ; m<26; m++){
                    alph[m] = 0;
                }
                i=0;
            }
        } 
        
    }

    cout << "Part 1 : " << result1 << endl;
    cout << "Part 2 : " << result2 << endl;


    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl; 

    return 0;
}
