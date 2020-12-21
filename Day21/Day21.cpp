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

int main() {
	auto start = high_resolution_clock::now();
	map<string,vector<string>> alph;
	vector<vector<string>> allIngredients;
	set<string> uniqueIngredients;
    vector<int> tilesId;
    ifstream in;
    in.open("Day21.txt");
    ull result = 0;
    string input;
    while (!in.eof()){
		string ingr;
		string allergs;
		vector<string> ingredients;
		vector<string> allerg;
        getline(in,input);
        ingr = split(input,"(contains")[0];
		allergs = split(input,"(contains ")[1];
		allergs = allergs.substr(0,allergs.length()-1);
		ingredients = split(ingr," ");
		allerg = split(allergs,", ");
		allIngredients.push_back(ingredients);
		uniqueIngredients.insert(ingredients.begin(),ingredients.end());

		for (auto v : allerg){
			if (alph.find(v) != alph.end()){
				for(int i=0 ; i < alph[v].size() ; i++){
					if (find(ingredients.begin(),ingredients.end(),alph[v][i]) == ingredients.end()){
						alph[v].erase(alph[v].begin()+i);
						i--;
					}
				}
			}
			else{
				alph[v] = ingredients;
			}
		}
    }

	vector<string> noAllerg ;
	for (auto a : uniqueIngredients){
		noAllerg.push_back(a);
	}
	for (auto c: alph){
		for (auto v : c.second){
			if (find(noAllerg.begin(),noAllerg.end(),v) != noAllerg.end())
				noAllerg.erase(find(noAllerg.begin(),noAllerg.end(),v));
		}
	}

	for (auto v : noAllerg){
		for (auto c : allIngredients){
			for (auto m : c){
				if (v == m)
					result++;
			}
		}
	}

	cout << "Part 1 : " << result << endl;

	//Part 2

	bool ok = false;
	map<string,string> uniqueAllerg;

	while(!ok){
		ok = true;
		string change;
		for (auto v : alph){
			if (v.second.size() == 1){
				uniqueAllerg[v.first] = v.second[0];
				change = v.second[0];
				v.second.clear();
				ok = false;
				break;
			}
		}

		for (auto v  = alph.begin() ; v != alph.end(); v++){
			if (find(v->second.begin(),v->second.end(),change) != v->second.end()){
				v->second.erase(find(v->second.begin(),v->second.end(),change));
			}
		}
	}

	string part2;
	for (auto v : uniqueAllerg){
		part2+=v.second+",";
	}

	part2 = part2.substr(0,part2.length()-1);
	cout << "Part2 : " << part2 << endl;

	auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time taken by program: "
         << duration.count() << " microseconds" << endl;
}
