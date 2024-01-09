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
#include<cmath>
using namespace std;

int gray[1024][1024];

int Get_power(int bits){
    return pow(2,bits);
}

void Gray_code(int bits){
    int number=(int)Get_power(bits);
    if(bits==1){
        gray[0][0]=0;
        gray[1][0]=1;
        return;
    }
    for(int i=0;i<number/2;i++){
        gray[i][bits-1]=0;
        gray[number-1-i][bits-1]=1;
    }

    Gray_code(bits-1);
    for(int i=number/2;i<number;i++){
        for(int j=0;j<bits-1;j++){
            gray[i][j]=gray[number-i-1][j];
        }
    }
}

void Print_Gray_code(int bits){
    int number=(int)Get_power(bits);
    for(int i=0;i<number;i++){
        for(int j=0;j<bits;j++){
            cout<<gray[i][bits-j-1]<<"   ";
        }
        cout<<endl;
    }
}

int Open_file(string filename){
    ifstream in_file;
    int bits=0;
    in_file.open(filename);
    string item;
    getline(in_file,item);
    while(in_file){
        getline(in_file,item);
        bits=stoi(item);
    }
    return bits;
}

void Write_file(string filename,int bits){
    ofstream of(filename);
    int number=(int)Get_power(bits);
    for(int i=0;i<number;i++){
        for(int j=0;j<bits;j++){
            of<<gray[i][bits-j-1]<<"   ";
        }
        of<<endl;
    }
    of.close();
}


int main(){
    string inputfilename="L://LAB/input_lab3.2.txt";
    string outputfilename="L://LAB/output_lab3.2.txt";
    int bits=Open_file(inputfilename);
    Gray_code(bits);
    Write_file(outputfilename,bits);
    Print_Gray_code(bits);
    system("pause");
}