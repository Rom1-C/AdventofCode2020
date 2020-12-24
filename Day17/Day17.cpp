#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include <set>

#define ull unsigned long long

using namespace std;
using namespace std::chrono;

int main(){
    auto start = high_resolution_clock::now();
    set<tuple<int,int,int>> alph;
    set<tuple<int,int,int,int>> save;
    ifstream in;
    in.open("Day17.txt");
    bool find;
    char input;
    int x=0;
    int y=0;
    while (!in.eof()){
        in.get(input);
        if (input == '#'){
            alph.insert({x,y,0});
            save.insert({x,y,0,0});
        }
        x++;
        
        if (x==8 && y == 7)
            break;

        if (x == 9){
            x = 0;
            y++;
        }
        
    }

    for (int i = 0 ; i < 6 ; i++){
        set<tuple<int,int,int>> alpb;
        for (int j = -1-i ; j < 9+i ; j++){
            for (int k = -1-i ; k <9+i ; k++){
                for (int l = -1-i ; l<2+i ; l++){
                    int num = 0;
                    for (int dj = -1 ; dj < 2 ; dj++){
                        for (int dk = -1 ; dk < 2 ; dk++){
                            for (int dl = -1 ; dl < 2 ; dl++){
                                if (dj != 0 || dk !=0 || dl != 0){
                                    if (alph.count({j+dj,k+dk,l+dl}) > 0){
                                        num ++;
                                    }
                                }
                            }
                        }
                    }

                    if (alph.count({j,k,l}) == 0 && num == 3){
                        alpb.insert({j,k,l});
                    }
                    if (alph.count({j,k,l}) > 0&& num==2 || num==3){
                        alpb.insert({j,k,l});
                    }
                }
            }
        }
        alph = alpb;
    }

    cout << "Part 1 : " << alph.size() << endl;

    for (int i = 0 ; i < 6 ; i++){
        set<tuple<int,int,int,int>> alpb;
        for (int j = -1-i ; j < 9+i ; j++){
            for (int k = -1-i ; k <9+i ; k++){
                for (int l = -1-i ; l<2+i ; l++){
                    for (int m = -1-i ; m<2+i ; m++){
                        int num = 0;
                        for (int dj = -1 ; dj < 2 ; dj++){
                            for (int dk = -1 ; dk < 2 ; dk++){
                                for (int dl = -1 ; dl < 2 ; dl++){
                                    for (int dm = -1 ; dm<2 ; dm++){
                                        if (dj != 0 || dk !=0 || dl != 0 || dm!=0){
                                            if (save.count({j+dj,k+dk,l+dl,m+dm}) > 0 ){
                                                num ++;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        if (save.count({j,k,l,m}) == 0 && num == 3){
                            alpb.insert({j,k,l,m});
                        }
                        if (save.count({j,k,l,m}) > 0 && num==2 || num==3){
                            alpb.insert({j,k,l,m});
                        }
                    }
                }
            }
        }
        save =alpb;
    }

    cout << "Part 2 : " << save.size() << endl;

    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl; 
}
