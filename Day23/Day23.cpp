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

struct Cup{
    Cup* next;
    ull value;
};

inline ull norm(ull n) { return (n-1) % 1000000 + 1; }
inline ull prev(ull n) { return norm(n + 1000000 - 1);}

int main() {
	auto start = high_resolution_clock::now();
	int alph[9];
    vector<Cup*> cups;
    Cup* one;
    int tmp[3];
    ifstream in;
    in.open("Day23.txt");
    ull result = 0;
    int i=0;
    char c;
    while (!in.eof()){
        in.get(c);
        alph[i] = c-'0';
        cups.push_back(new Cup());
        cups.back()->value = c-'0';
        if (c == '1')
            one = cups.back();
        if (cups.size() == 9)
            break;
        i++;
    }
    
    //Part 1
    for (int j=0 ; j < 100 ; j++){
        tmp[0] = alph[(j+1)%9];
        tmp[1] = alph[(j+2)%9];
        tmp[2] = alph[(j+3)%9];
        int k = alph[j%9];
        int dest=-1;
        while (k>0){
            k--;
            for (int m = 4 ; m <9; m++){
                if (alph[(j+m)%9] == k){
                    dest = (j+m)%9;
                    break;
                }
            }
            if (dest!=-1)
                break;
        }
        if (k == 0){
            int max = -1;
            for (int m = 4 ; m <9; m++){
                if (alph[(j+m)%9] > max){
                    max = alph[(j+m)%9];
                    dest = (j+m)%9;
                }
            }
        }
        int lenght = abs((9+dest)-((j+3)%9))%9;
        for (int m = 1 ;m <= lenght ; m++){
            alph[(j+m)%9] = alph[(j+3+m)%9];
        }
        for (int m = 1 ;m <=3 ; m++){
            alph[(j+m+lenght)%9] = tmp[m-1];
        }
    }

    int un;
    for (int j=0 ; j < 9 ; j++){
        if (alph[j]==1)
            un = j;
    }

    cout << "Part 1 : ";
    for (int j=1 ; j < 9 ; j++){
        cout << alph[(un+j)%9];
    }
    cout << endl;
    
    //Part2
    for (int j = 9 ; j < 1000000 ; j++){
        cups.push_back(new Cup());
        cups.back()->value = j+1;
    }

    for (int j = 0 ; j < 1000000-1 ; j++){
        cups[j]->next = cups[j+1];
    }
    cups[cups.size()-1]->next = cups[0];

    vector<Cup*> reverse;
    reverse.reserve(1000000);
    for (Cup* c : cups){
        reverse[c->value] = c;
    }
    
    Cup* curr = cups[0];

    for (ull j = 0 ; j < 10000000 ; j++){
        ull dest = prev(curr->value);
        Cup* nope = curr->next;
        vector<ull> tmp = {curr->next->value,curr->next->next->value,curr->next->next->next->value};
        for (int m = 0 ; m < 3 ; m++){
            if (find(tmp.begin(),tmp.end(),dest) != tmp.end()){
                dest = prev(dest);
            }
        }

        Cup* rejoin = nope->next->next->next;
        curr->next = rejoin;

        Cup* dest_node = reverse[dest];
        Cup* dest_next = dest_node->next;
        dest_node->next = nope;
        nope->next->next->next = dest_next;

        curr = rejoin;
        
    }

    cout << "Part 2 : " << one->next->value * one->next->next->value << endl;

	auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time taken by program: "
         << duration.count() << " microseconds" << endl;
}
