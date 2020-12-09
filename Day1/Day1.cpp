#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main(){
    auto start = high_resolution_clock::now();
    FILE * fp = fopen("Day1.txt","r");
    int num[201];
    int i=0;
    while (!feof(fp)){
        fscanf(fp,"%d", &num[i]);
        i++;
    }

    for (i=0 ; i< 201 ; i++){
        for (int j = i+1 ; j< 201 ; j++){
            if (num[i] + num[j] < 2020){
                for (int k = j+1 ; k<201 ; k++){
                    if (num[i] + num[j] + num[k] == 2020){
                        cout << num[i]*num[j]*num[k] << endl;
                        cout << i << ": " << num[i] << endl;
                        cout << j << ": " << num[j] <<endl;
                        cout << k << ": " << num[k] <<endl;
                        break;
                    }
                }
            }
        }
    }

    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl; 
}
