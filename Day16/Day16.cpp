#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#define ull unsigned long long

using namespace std;
using namespace std::chrono;

vector<string> split(const string& str, const string& delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

int main(){
    auto start = high_resolution_clock::now();
    vector<pair<vector<int>,vector<int>>> rules;
    vector<pair<vector<int>,bool>> tickets;
    vector<int> myTickets;
    vector<string> tmp;
    vector<int> transi1;
    vector<int> transi2;
    ull result = 0;
    ifstream in;
    in.open("Day16.txt");
    size_t found;
    string input = "0";
    while(input != "your"){
        in >> input;
        found = input.find('-');
        if (found != string::npos){
            transi1.push_back(atoi(input.substr(0,found).c_str()));
            transi1.push_back(atoi(input.substr(found+1,input.length()).c_str()));
            in >> input;
            in >> input;
            found = input.find('-');
            transi2.push_back(atoi(input.substr(0,found).c_str()));
            transi2.push_back(atoi(input.substr(found+1,input.length()).c_str()));
            rules.push_back({transi1,transi2});
        }
        transi1.clear();
        transi2.clear();
        tmp.clear();
    }

    // My tickets
    getline(in,input);
    getline(in,input);
    tmp = split(input,",");
    for (auto v : tmp){
        myTickets.push_back(atoi(v.c_str()));
    }

    while (input != "nearby tickets:"){
        getline(in,input);
    }

    while (!in.eof()){
        getline(in,input);
        tmp = split(input,",");
        for (auto v : tmp){
            transi1.push_back(atoi(v.c_str()));
        }
        tickets.push_back({transi1,true});
        transi1.clear();
    }  

    //Part 1
    bool ok = false;
    for (int i = 0 ; i < tickets.size() ; i++){
        for (auto c : tickets[i].first){
            for (auto p : rules){
                if (c >= p.first[0] && c <= p.first[1] || c >= p.second[0] && c <= p.second[1])
                    ok = true;
            }
            
            if (!ok){
                tickets[i].second = false;
                result +=c;
            }
            else{
                ok = false;
            }
        }
    }

    cout << "Part 1 : " << result << endl;

    // Part 2
    result = 1;
    bool field[20][20];
    for (int m = 0 ; m < 20 ; m++){
        for (int n = 0 ; n < 20 ; n++)
            field[m][n] = true;
    }
    for (auto v : tickets){
        if (v.second){
            for (int j = 0 ; j < v.first.size() ; j++){
                for (int i = 0 ; i < rules.size() ; i++){
                    if ( !(v.first[j] >= rules[i].first[0] && v.first[j] <= rules[i].first[1] || v.first[j] >= rules[i].second[0] && v.first[j] <= rules[i].second[1])){
                        field[j][i] = false;
                    }
                }
            }
        }
    }

    int ticketfields[20];
    bool tooMuch[20];
    for (int m = 0 ; m < 20 ; m++){
        tooMuch[m] = false;
    }
    int find = 0;

    while (find != 20){
        for (int i = 0 ; i < 20 ; i++){
            vector<int> nice;
            for (int j = 0 ; j < 20 ; j++){
                if (field[i][j] != 0 && !tooMuch[j]){
                    nice.push_back(j);
                }
            }
            if (nice.size() == 1){
                ticketfields[i] = nice[0];
                tooMuch[nice[0]] = true;
                find++;
            }
        }
    }

    for (int i = 0 ; i < 20 ; i++){
        if (ticketfields[i] < 6){
            result*=myTickets[i];
        }
    }

    cout << "Part 2 : " << result << endl;

    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time taken by program: "
         << duration.count() << " microseconds" << endl; 
}
