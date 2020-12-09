#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;
using namespace std::chrono;

std::vector<std::string> split(const std::string & src, char delim) {
   using namespace std;
   vector<string> v;
   auto p = begin(src);
   for(auto q = find(p, end(src), delim); q != end(src); q = find(++p, end(src), delim)) {
      v.emplace_back(p, q);
      p = q;
   }
   if (p != end(src))
      v.emplace_back(p, end(src));
   return v;
}

int main(){
    auto start = high_resolution_clock::now();
    ifstream in;
    vector <pair<string,string>> found;
    vector <pair<string,string>> find;
    vector <pair<string,string>> totalFind;
    vector <string> alph[594];
    in.open("Day7.txt");
    string tmp;
    int count, result;
    bool good ;
    result =0;
    int i=0;
    count =1;
    while (!in.eof()){
        getline(in,tmp);
        alph[i] = split(tmp,' ');
        i++;
    }
    

    // Part 1
    found.push_back({"shiny","gold"});
    while (count !=0){
        count=0;
        for (int j=0 ; j < 594 ; j++){
            for (pair<string,string> v : found){
                for (int k = 4 ; k < alph[j].size()-1 ; k++){
                    if (alph[j][k].find(v.first) != std::string::npos && alph[j][k+1].find(v.second) != std::string::npos){
                        good = true;
                        for (auto st : totalFind){
                            if (st.first == alph[j][0] && st.second == alph[j][1])
                                good = false;
                        }
                        if (good){
                            find.push_back({alph[j][0],alph[j][1]});
                            totalFind.push_back({alph[j][0],alph[j][1]});
                            result++;
                            count++;
                        }
                    }
                }
            }
        }

        found.clear();
        found.insert(found.end(), find.begin(), find.end());
        find.clear();
    }

    cout << "Part 1 : " << result << endl;

    //Part 2
    result = 0;
    count = 1;
    found.clear();
    find.clear();
    found.push_back({"shiny","gold"});
    while (count !=0){
    count=0;
    for (int j=0 ; j < 594 ; j++){
        for (pair<string,string> v : found){
            if (alph[j][0] == v.first && alph[j][1] == v.second){
                if (alph[j][4][0] > 48 && alph[j][4][0] < 57){
                    for (int k=0 ; k < atoi(alph[j][4].c_str()) ; k++){
                        find.push_back({alph[j][5],alph[j][6]});
                        result++;
                        count++;
                    }
                }
                if (alph[j].size() < 8)
                    continue;
                for (int k = 8 ; k < alph[j].size() ; k++){
                    if (alph[j][k] == "bags," || alph[j][k] == "bag," || alph[j][k] == "bag." || alph[j][k] == "bags."){
                        if (alph[j][k-3][0] > 48 && alph[j][k-3][0] < 57){
                            for (int m=0 ; m < atoi(alph[j][k-3].c_str()) ; m++){
                                find.push_back({alph[j][k-2],alph[j][k-1]});
                                result++;
                                count++;
                            }
                        }
                    }
                }
            }
        }
    }

    found.clear();
    found.insert(found.end(), find.begin(), find.end());
    find.clear();
    }

    cout << "Part 2 : " << result << endl;


    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl; 

    return 0;
}
