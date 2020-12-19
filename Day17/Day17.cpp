#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>

#define ull unsigned long long

using namespace std;
using namespace std::chrono;

bool present(vector<tuple<int,int,int>> vect , tuple<int,int,int> t){
    for (auto v : vect){
        if (get<0>(v) == get<0>(t) && get<1>(v) == get<1>(t) && get<2>(v) == get<2>(t))
            return true;
    }
    return false;
}

bool present2(vector<tuple<int,int,int,int>> vect , tuple<int,int,int,int> t){
    for (auto v : vect){
        if (get<0>(v) == get<0>(t) && get<1>(v) == get<1>(t) && get<2>(v) == get<2>(t) && get<3>(v) == get<3>(t))
            return true;
    }
    return false;
}

int main(){
    auto start = high_resolution_clock::now();
    vector<tuple<int,int,int>> alph;
    vector<tuple<int,int,int,int>> save;
    ifstream in;
    in.open("Day17.txt");
    bool find;
    char input;
    int x=0;
    int y=0;
    while (!in.eof()){
        in.get(input);
        if (input == '#'){
            alph.push_back({x,y,0});
            save.push_back({x,y,0,0});
        }
        x++;
        
        if (x==8 && y == 7)
            break;

        if (x == 9){
            x = 0;
            y++;
        }
        
    }

    cout << alph.size() << endl;

    for (int i = 0 ; i < 6 ; i++){
        vector<tuple<int,int,int>> alpb;
        for (int j = -1-i ; j < 9+i ; j++){
            for (int k = -1-i ; k <9+i ; k++){
                for (int l = -1-i ; l<2+i ; l++){
                    int num = 0;
                    for (int dj = -1 ; dj < 2 ; dj++){
                        for (int dk = -1 ; dk < 2 ; dk++){
                            for (int dl = -1 ; dl < 2 ; dl++){
                                if (dj != 0 || dk !=0 || dl != 0){
                                    if (present(alph,{j+dj,k+dk,l+dl})){
                                        num ++;
                                    }
                                }
                            }
                        }
                    }

                    if (!present(alph,{j,k,l}) && num == 3 && !present(alpb,{j,k,l})){
                        alpb.push_back({j,k,l});
                    }
                    if (present(alph,{j,k,l}) && num==2 || num==3 && !present(alpb,{j,k,l})){
                        alpb.push_back({j,k,l});
                    }
                }
            }
        }
        alph.clear();
        for (auto v : alpb){
            alph.push_back(v);
        }
    }

    cout << "Part 1 : " << alph.size() << endl;

    for (int i = 0 ; i < 6 ; i++){
        vector<tuple<int,int,int,int>> alpb;
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
                                            if (present2(save,{j+dj,k+dk,l+dl,m+dm})){
                                                num ++;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        if (!present2(save,{j,k,l,m}) && num == 3 && !present2(alpb,{j,k,l,m})){
                            alpb.push_back({j,k,l,m});
                        }
                        if (present2(save,{j,k,l,m}) && num==2 || num==3 && !present2(alpb,{j,k,l,m})){
                            alpb.push_back({j,k,l,m});
                        }
                    }
                }
            }
        }
        save.clear();
        for (auto v : alpb){
            save.push_back(v);
        }
    }

    cout << "Part 2 : " << save.size() << endl;

    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl; 
}
