#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <regex>

#define ull unsigned long long

using namespace std;
using namespace std::chrono;
string solve(string s, bool part2);

unordered_map<string,vector<string>> alph;
unordered_map<string,string> dP;

vector<string> split(const string& str, const string& delim){
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

string solve_bis(string s,bool part2){
    if (s[0] == '"'){
        return string(1,s[1]);
    }
    else if (s == "|"){
        return "|";
    }
    else{
        return "(" + solve(s,part2) + ")";
    }
}

string solve(string s, bool part2){
    if (s == "8" && part2){
        return "(" + solve_bis("42",part2) + ")+";
    }
    if (s == "11" && part2){
        string result = "";
        for (int i = 1 ;i < 7; i++){
            for (int j = 0 ; j< i ; j++){
                result+=solve_bis("42",part2);
            }
            for (int j = 0 ; j< i ; j++){
                result+=solve_bis("31",part2);
            }
            result+="|";
        }
        result = result.substr(0,result.length()-1);
        return result;
    }
    if (dP.find(s) != dP.end()){
        return dP[s];
    }
    string res = "";
    for (auto v : alph[s]){
        res+=solve_bis(v,part2);
    }
    dP[s] = res;
    return res;
}

int main(){
    auto start = high_resolution_clock::now();
    vector<int> toFind;
    vector<int> found;
    vector<string> messages;
    vector<string> tmp;
    ifstream in;
    in.open("Day19.txt");
    int result = 0;
    bool find;
    string input = "c";
    while (!input.empty()){
        getline(in,input);
        if (input.size() ==0)
            break;
        tmp = split(input,":");
        alph[tmp[0]] = split(tmp[1]," ");
    }

    while (!in.eof()){
        getline(in,input);
        messages.push_back(input);
    }

    regex part1(solve("0",false));

    for (auto v : messages){
        if (regex_match(v,part1)){
            result++;
        }
    }

    cout << "Part 1 : " << result << endl;

    result = 0;
    dP.clear();

    regex part2(solve("0",true));

    for (auto v : messages){
        if (regex_match(v,part2)){
            result++;
        }
    }

    cout << "Part 2 : " << result << endl;

    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl; 
}
