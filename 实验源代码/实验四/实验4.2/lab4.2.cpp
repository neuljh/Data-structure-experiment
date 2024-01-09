#include<iostream>
#include<string>
#include<stack>
#include<cstdlib> 
#include<sstream> 
#include<vector>
#include<stdio.h>
#include<malloc.h>
#include <stdlib.h>
#include <limits.h>
#include<fstream>
#include<math.h>
using namespace std;

int dp[1024][1024];


template<class T>
vector<T> &Open_file(string filename,vector<T> &store){
    ifstream in_file;
    in_file.open(filename);
    string item;
    getline(in_file,item);
    int length=stoi(item);
    store.push_back(item);
    for(int index=1;index<length;index++){
        for(int i=0;i<length-index;i++){
            if(i==length-index-1){
                getline(in_file,item);
            }else{
                getline(in_file,item,' ');
            }
            store.push_back(item);
        }
    }
    getline(in_file,item);
    store.push_back(item);
    return store;
}

void Write_file(string filename,int res){
    ofstream of(filename);
    of<<res<<endl;
    of.close();
}

int solution(vector<int> &rent,int sum){
    int index=0;
    for(int i=0;i<sum;i++){
        for(int j=i;j<sum;j++){
            if(i==j){
                dp[i][j]=0;
                continue;
            }else{
                dp[i][j]=rent[index];
                index++;
            }
        }
    }
    for(int i=0;i<sum;i++){
        for(int j=i;j<sum;j++){
            if(i==j){
                continue;
            }else{
                int temp=INT_MAX;
                for(int k=i;k<=j;k++){
                    temp=min(temp,dp[i][k]+dp[k][j]);
                }
                dp[i][j]=temp;
            }
        }
    }
    for(int i=0;i<sum;i++){
        for(int j=i;j<sum;j++){
            dp[j][i]=dp[i][j];
        }
    }
    return dp[0][sum-1];
}

void Print_dp(vector<int> &rent,int sum){
    for(int i=0;i<sum;i++){
        for(int j=0;j<sum;j++){
            cout<<dp[i][j]<<" ";
        }
        cout<<endl;
    }
}


int main(){
    vector<string> store;
    string filename="L://LAB/input_lab4.2.txt";
    string outfilename="L://LAB/output_lab4.2.txt";
    int length;
    vector<int> rent;
    store=Open_file(filename,store);
    for(int i=0;i<store.size();i++){
        if(i==0){
            length=stoi(store[i]);
        }else{
            rent.push_back(stoi(store[i]));
        }
    }
    Write_file(outfilename,solution(rent,length));
    Print_dp(rent,length);
    system("pause");
}


    // vector<int> rent{5,15,7};
    // int length=3;
    // cout<<solution(rent,length);
    // system("pause");