#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <fstream>

#define N 95

using namespace std;
using namespace std::chrono;

int main(){
    auto start = high_resolution_clock::now();
    int a = N;
    int b = N;
    ifstream in;
    in.open("Day11.txt");
    bool finished = false;
    int result = 0;
    char input[N][N];
    char copy[N][N];
    char save[N][N];
    int i=0;
    int j=0;
    while (!in.eof()){
        in >> input[i][j];
        j++;
        if (j==b){
            i++;
            j = 0;
        }
    }

    for (int m = 0 ; m < a ; m++){
        for (int n = 0 ; n<b ; n++){
            save[m][n] = input[m][n];
        }
    }

    //Part 1
    while (!finished){
        finished = true;

        for (int m = 0 ; m< a ; m++){
            for ( int n =0 ; n<b ; n++){
                int h=0;
                if (input[m][n] == '.')
                    copy[m][n] = '.';
                else{
                    for (int k = -1 ; k<2 ; k++){
                        for (int l = -1 ; l<2 ; l++){
                            if (l!=0 || k!=0){
                                int mk = m+k;
                                int nl = n+l;
                                if (mk >= 0 && mk < a && nl >=0 && nl <a && input[mk][nl] =='#')
                                    h++;
                            }
                        }
                    }
                    if (input[m][n] == 'L'){
                        if (h>0)
                            copy[m][n] = 'L';
                        else
                            copy[m][n] = '#';
                    }
                    if (input[m][n] == '#'){
                        if (h>=4)
                            copy[m][n] = 'L';
                        else
                            copy[m][n] = '#';
                    }
                }
            }
        }

        for (int m = 0 ; m < a && finished ; m++){
            for (int n = 0 ; n<b && finished; n++){
                if (copy[m][n] != input[m][n]){
                    finished = false;
                }
            }
        }

        for (int m = 0 ; m < a ; m++){
            for (int n = 0 ; n<b ; n++){
                input[m][n] = copy[m][n];
            }
        }
        //cout << finished << endl;
    }

    for (int m = 0 ; m < a; m++){
        for (int n = 0 ; n<b; n++){
            if (input[m][n] == '#')
                result++;
        }
    }

    std::cout << "Part 1 : " << result << endl;  

    //Part 2

    for (int m = 0 ; m < a ; m++){
        for (int n = 0 ; n<b ; n++){
            input[m][n] = save[m][n];
        }
    }

    result = 0;
    finished = false;
    while (!finished){
        finished = true;

        for (int m = 0 ; m< a ; m++){
            for ( int n =0 ; n<b ; n++){
                int h=0;
                if (input[m][n] == '.')
                    copy[m][n] = '.';
                else{
                    for (int k = -1 ; k<2 ; k++){
                        for (int l = -1 ; l<2 ; l++){
                            if (l!=0 || k!=0){
                                int mk = m+k;
                                int nl = n+l;
                                while(mk >= 0 && mk < a && nl >=0 && nl <a && input[mk][nl] =='.'){
                                    mk+=k;
                                    nl+=l;
                                }
                                if (mk >= 0 && mk < a && nl >=0 && nl <a && input[mk][nl] =='#')
                                    h++;
                            }
                        }
                    }
                    if (input[m][n] == 'L'){
                        if (h>0)
                            copy[m][n] = 'L';
                        else
                            copy[m][n] = '#';
                    }
                    if (input[m][n] == '#'){
                        if (h>=5)
                            copy[m][n] = 'L';
                        else
                            copy[m][n] = '#';
                    }
                }
            }
        }

        for (int m = 0 ; m < a && finished ; m++){
            for (int n = 0 ; n<b && finished; n++){
                if (copy[m][n] != input[m][n]){
                    finished = false;
                }
            }
        }

        for (int m = 0 ; m < a ; m++){
            for (int n = 0 ; n<b ; n++){
                input[m][n] = copy[m][n];
            }
        }
    }

    for (int m = 0 ; m < a; m++){
        for (int n = 0 ; n<b; n++){
            if (input[m][n] == '#')
                result++;
        }
    }  

    cout << "Part 2 : " << result << endl;

    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl; 
}
