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


int dp[1024][1024]={0};
int ddpp[1024][1024]={0};
int test[1024][1024]={0};
int res[1024]={0};

int Min(int a,int b){
    return a<=b?a:b;
}

int solution2(vector<int> &money,int target){
    for(int i=1;i<=target;i++){
        res[i]=INT_MAX-10000;
    }
    for(int i=1;i<=target;i++){
        for(int j=0;j<money.size();j++){
            int temp=INT_MAX;
            if(i-money[j]>=0){
                temp=min(res[i-money[j]]+1,res[i]);
                res[i]=temp;
            }
        }
    }
    return res[target];
}

int solution1(vector<int> &money,int target){
    for(int i=0;i<money.size();i++){
        dp[i][0]=0;
    }
    for(int j=0;j<=target;j++){
        if(j%money[0]==0){
            dp[0][j]=j/money[0];
            // dp[0][j]=1;
        }else{
            dp[0][j]=(int)ceil((double)j/money[0]);
        }
    }
    for(int i=1;i<money.size();i++){
        for(int j=1;j<=target;j++){
            int temp=INT_MAX;
            for(int k=0;j-k*money[i]>=0;k++){
                temp=Min(dp[i-1][j-k*money[i]]+k,temp);
            }
            dp[i][j]=temp;
        }
    }
    return dp[money.size()-1][target];
}

int solution(vector<int> &money,int target){
    for(int i=0;i<money.size();i++){
        dp[i][0]=0;
    }
    for(int j=0;j<=target;j++){
        if(j%money[0]==0){
            dp[0][j]=j/money[0];
            // dp[0][j]=1;
        }else{
            dp[0][j]=(int)ceil((double)j/money[0]);
        }
    }
    for(int i=1;i<money.size();i++){
        for(int j=1;j<=target;j++){
            int temp=INT_MAX;
            for(int k=0;j-k*money[i]>=0;k++){
                temp=Min(dp[i-1][j-k*money[i]]+k,temp);
                if(j==k*money[i]||test[i-1][j-k*money[i]]==1){
                    test[i][j]=1;
                }
            }
            dp[i][j]=temp;
        }
    }
    return dp[money.size()-1][target];
}

void Print_dp(vector<int> &money,int target){
    cout<<"      ";
    for(int i=0;i<=target;i++){
        cout<<i<<"yuan    ";
    }
    cout<<endl;
    for(int j=0;j<money.size();j++){
        for(int i=0;i<=target;i++){
            cout<<money[j]<<"yuan: ";
            cout<<dp[j][i]<<" ";
        }
        cout<<endl;
    }
}

void correct(vector<int> &money,int target){
    for(int i=0;i<money.size();i++){
        for(int j=1;j<=target;j++){
           if(test[i][j]==0){
               dp[i][j]=-1;
           }
        }
    }
}


int change(vector<int> &money,int target){
    for(int i=0;i<money.size();i++){
        ddpp[i][0]=1;
    }
    for(int j=0;j<=target;j++){
        if(j%money[0]==0){
            ddpp[0][j]=1;
        }else{
            ddpp[0][j]=0;
        }
    }
    
    for(int i=1;i<money.size();i++){
        for(int j=1;j<=target;j++){
            int temp=0;
            for(int k=0;j-k*money[i]>=0;k++){
                temp+=ddpp[i-1][j-k*money[i]];
            }
            ddpp[i][j]=temp;
        }
    }
    return ddpp[money.size()-1][target];
}

template<class T>
vector<T> &Open_file(string filename,vector<T> &store){
    ifstream in_file;
    in_file.open(filename);
    string item;
    getline(in_file,item);
    int length=stoi(item);
    store.push_back(item);
    for(int i=0;i<length;i++){
        if(i==length-1){
            getline(in_file,item);
        }else{
            getline(in_file,item,' ');
        }
        store.push_back(item);
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

int main(){
    // vector<string> store;
    // string filename="L://LAB/input_lab4.1.txt";
    // string outfilename="L://LAB/output_lab4.1.txt";
    // int money_number;
    // vector<int> money;
    // int target;
    // store=Open_file(filename,store);
    // for(int i=0;i<store.size();i++){
    //     if(i==0){
    //         money_number=stoi(store[i]);
    //     }else if(i==store.size()-1){
    //         target=stoi(store[i]);
    //     }else{
    //         money.push_back(stoi(store[i]));
    //     }
    // }
    // if(money[0]!=1){
    //     money.insert(money.begin(),1);
    // }
    // Write_file(outfilename,solution(money,target));
    // cout<<"The final result of the dynamic programming calculation is:"<<endl;
    // correct(money,target);
    // Print_dp(money,target);

    vector<int> money{2,5,11};
    int target=18;
    cout<<solution2(money,target)<<endl;
    system("pause");
}


    // vector<int> money{2,5,11};
    // int target=18;


    // // cout<<solution(money,target)<<endl;
    // // cout<<"1:"<<endl;
    // // Print_dp(money,target);
    // // cout<<endl;
    // // correct(money,target);
    // // cout<<"2:"<<endl;
    // // Print_dp(money,target);
    // cout<<check(money,money.size(),target)<<endl;
    // // cout<<coin_change(money,target)<<endl;



 // vector<int> money{2,3};
    // int target=7;
    // cout<<ca(target,money)<<endl;

    // cout<<solution(money,target)<<endl;
    // cout<<"1:"<<endl;
    // Print_dp(money,target);
    // cout<<endl;
    // correct(money,target);
    // cout<<"2:"<<endl;
    // Print_dp(money,target);
    // // cout<<check(money,money.size(),target)<<endl;
    //     cout<<coin_change(money,target)<<endl;


    // // for(int i=1;i<money.size();i++){
    // //     for(int j=1;j<=target;j++){
    // //         cout<<check(money,i,j)<<" ";
    // //     }
    // // }

    // int check(vector<int> &money,int m,int n){
//     int sum=0;
//     for(int i=m-1;i>=0;i--){
//         int index=0;
//         while(index*money[i]<=n){
//             index++;
//         }
//         n=n-(index-1)*money[i];
//         sum=sum+index-1;
//         if(n==0){
//             break;
//         }
//     }
//     return sum;
// }

// void correct(vector<int> &money,int target){
//     for(int i=0;i<money.size();i++){
//         for(int j=1;j<=target;j++){
//             if(check(money,i+1,j)!=dp[i][j]){
//                 dp[i][j]=INT_MAX;
//             }
//         }
//     }
// }