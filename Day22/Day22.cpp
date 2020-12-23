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
#include <queue>

#define ull unsigned long long

using namespace std;
using namespace std::chrono;

queue<int> j1p2;
queue<int> j2p2;

int part2(queue<int> j1, queue<int> j2){
    set<pair<queue<int>,queue<int>>> history;

    while (j1.size() != 0 && j2.size() != 0){
        if (history.count({j1,j2})){
            j1p2 = j1;
            j2p2 = j2;
            return 1;
        }
        history.insert({j1,j2});
        int c1 = j1.front();
        int c2 = j2.front();
        j1.pop();
        j2.pop();
        int winner=0;

        if (j1.size() >= c1 && j2.size() >=c2){
            queue<int> tmp = j1;
            queue<int> sub1;
            for (int i = 0 ; i < c1 ; i++){
                sub1.push(tmp.front());
                tmp.pop();
            }
            tmp = j2;
            queue<int> sub2;
            for (int i = 0 ; i < c2 ; i++){
                sub2.push(tmp.front());
                tmp.pop();
            }
            winner = part2(sub1,sub2);
        }
        else if (c1>c2)
            winner = 1;
        else{
            winner = 2;
        }

        if (winner==1){
            j1.push(c1);
            j1.push(c2);
        }
        else { 
            j2.push(c2);
            j2.push(c1);
        }
    }

    j1p2 = j1;
    j2p2 = j2;
    if (j1.size() > 0)
        return 1;
    else{
        return 2;
    }
}

int win(queue<int> q){
    int result = 0;
    int c1;
    while (q.size()>0){
            c1 = q.front();
            q.pop();
            result+=c1*(q.size()+1);
    }
    return result;
}

int main() {
	auto start = high_resolution_clock::now();
	queue<int> j1;
    queue<int> j2;
    ifstream in;
    in.open("Day22.txt");
    ull result = 0;
    string input;
    getline(in,input);
    getline(in,input);
    while (!input.empty()){
        j1.push(atoi(input.c_str()));
		getline(in,input);
    }

    getline(in,input);

    while (!in.eof()){
		getline(in,input);
        j2.push(atoi(input.c_str()));
    }
    
    j1p2 = j1;
    j2p2 = j2;
    //Part 1
    int c1;
    int c2;

    while (j1.size() != 0 && j2.size() !=0){
        c1 = j1.front();
        c2 = j2.front();
        j1.pop();
        j2.pop();

        if (c1>c2){
            j1.push(c1);
            j1.push(c2);
        }
        else { 
            j2.push(c2);
            j2.push(c1);
        }
    }

    if (j1.size() != 0){
        while (j1.size()>0){
            c1 = j1.front();
            j1.pop();
            result+=c1*j1.size()+1;
        }
    }
    else{
        while (j2.size()>0){
            c1 = j2.front();
            j2.pop();
            result+=c1*(j2.size()+1);
        }
    }

    cout << "Part 1 : " << result << endl;

    //Part 2
    result = 0;
    int winner = part2(j1p2,j2p2);

    if (winner == 2){
        result = win(j2p2);
    }
    else{
        result = win(j1p2);
    }

    cout << "Part 2 : " << result << endl;

	auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time taken by program: "
         << duration.count() << " microseconds" << endl;
}
