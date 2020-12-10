#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

int main(){
   auto start = high_resolution_clock::now();
   int result[4];
   vector<int> alph;
   result[1] = 0;
   result[3] = 0;
   int altern = 1;
   long long tmp;
   ifstream in;
   in.open("Day10.txt");
   while (in >> tmp){
      alph.push_back(tmp);
   }

   alph.push_back(0);
   sort(alph.begin(),alph.end());

    // Part 1
    result[3] = 1;

    for (int j = 0 ; j< alph.size()-1 ; j++){
        if ((alph[j+1]-alph[j]) > 3)
            break;
        result[alph[j+1]-alph[j]]++;
    }
   cout << "Part 1 : " << result[1]*result[3] << endl;


   //Part 2
   vector<int64_t> nums(alph.size());

   nums[alph.size()-1] = 1;
   for (int i = alph.size()-2 ; i >=0 ; i--){
       for(int j=i+1 ; j< alph.size() && alph[j] - alph[i] <=3 ; j++){
           nums[i]+=nums[j];
       }
   }
    cout << "Part 2 : " << nums[0] << endl;

   auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl; 

   return 0;
}
