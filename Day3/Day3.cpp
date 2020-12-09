#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main(){
    auto start = high_resolution_clock::now();
    int a = 323;
    int b = 31;
    FILE * fp = fopen("Day3.txt","r");
    char input[323][31];
    int i=0;
    int j=0;
    while (!feof(fp)){
        fscanf(fp,"%c", &input[i][j]);
        j++;
        if (j==b+1){
            i++;
            j = 0;
        }
    }

    long long result = 0;
    long long result2 = 0;
    for (i=0 ; i<= a ; i++){
        if (input[i][(i*3)%b] == '#')
            result ++;
    }

    cout << "Part 1 : " << result << endl;

    for (i=0 ; i<= a ; i++){
        if (input[i][i%b] == '#')
            result2 ++;
    }

    result*=result2;
    result2=0;
    for (i=0 ; i<= a ; i++){
        if (input[i][(i*5)%b] == '#')
            result2 ++;
    }

    result*=result2;
    result2=0;

    for (i=0 ; i<= a ; i++){
        if (input[i][(i*7)%b] == '#')
            result2 ++;
    }
    result*=result2;
    result2=0;

    for (i=0 ; i*2<= a ; i++){
        if (input[i*2][i%b] == '#')
            result2 ++;
    }

    result*=result2;
    result2=0;

    cout << "Part 2 : " << result << endl;    

    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl; 
}
