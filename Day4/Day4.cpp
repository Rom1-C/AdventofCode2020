#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <string>
#include <fstream>

using namespace std;
using namespace std::chrono;

int main(){
    auto start = high_resolution_clock::now();
    ifstream in;
    char c;
    in.open("Day4.txt");
    bool cid, good;
    good = true;
    string tmp,id, value;
    int first,count;
    int i=0;
    count =0;
    while (!in.eof()){
        in >> tmp;
        first = tmp.find(':');
        id = tmp.substr(0,first);
        value = tmp.substr(first+1, tmp.length());
        if (id == "cid"){
            cid = true;
        }
        else if (id =="byr"){
            if (value.length() != 4)
                good = false;
            if (atoi(value.c_str()) < 1920 || atoi(value.c_str()) > 2002)
                good = false;
        }
        else if(id == "iyr"){
            if (value.length() != 4)
                good = false;
            if (atoi(value.c_str()) < 2010 || atoi(value.c_str()) > 2020)
                good = false;
        }
        else if(id == "hgt"){
            if (value.length() < 4)
                good = false;
            else if (value.substr(3,value.length()) == "cm"){
                if (atoi(value.substr(0,3).c_str()) < 150 || atoi(value.substr(0,3).c_str()) > 193)
                    good = false;
            }
            else if (value.substr(2,value.length()) == "in"){
                if (atoi(value.substr(0,2).c_str()) < 59 || atoi(value.substr(0,2).c_str()) > 76)
                    good = false;
            }
            else{
                good = false;
            }
        }
        else if (id == "eyr"){
            if (value.length() != 4)
                good = false;
            if (atoi(value.c_str()) < 2020 || atoi(value.c_str()) > 2030)
                good = false;
        }
        else if(id == "hcl"){
            if (value.substr(0,1) != "#")
                good = false;
            else if (value.length() !=7){
                good = false;
            }
            else{
                for (int j = 1 ; j < value.length(); j++){
                    if (value.c_str()[j] < 48 || value.c_str()[j] > 57 && value.c_str()[j] < 97 || value.c_str()[j] > 102)
                        good = false;
                }
            }
        }
        else if (id == "ecl"){
            if (value != "amb" && value != "blu" && value != "brn" && value != "gry" && value != "grn" && value != "hzl" && value != "oth")
                good = false;
        }
        else if (id == "pid"){
            if (value.length() != 9)
                good = false;
            for (int j = 0 ; j < value.length(); j++){
                    if (value.c_str()[j] < 48 || value.c_str()[j] > 57 )
                        good = false;
                }
        }

        i++;
        if (in.peek()=='\n'){
            in.get(c);
            if (in.peek()=='\n'){
                in.get(c);
                if ((i == 8 || i == 7 && !cid ) && good){
                    count ++;
                }
                cid = false;
                good = true;
                i = 0;
            }
        } 
        
    }

    cout << "Part 2 : " << count << endl;


    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl; 

    return 0;
}
