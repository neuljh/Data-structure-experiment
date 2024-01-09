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
using namespace std; 

class Advertisement{
    private:
        int id;
        int amount;
        string name;
        string e_mail;
        string start_time;
        string end_time;
    public:
        Advertisement(int id,int amount,string name,string e_mail,string start_time,string end_time){
            this->id=id;
            this->amount=amount;
            this->name=name;
            this->e_mail=e_mail;
            this->start_time=start_time;
            this->end_time=end_time;
        }
        // ~Advertisement(){
        //     cout<<"class Advertisement is destroyed......"<<endl;
        // }
        int getId(){
            return this->id;
        }
        int getAmount(){
            return this->amount;
        }
        string getName(){
            return this->name;
        }
        string getE_mail(){
            return this->e_mail;
        }
        string getStart_time(){
            return this->start_time;
        }
        string getEnd_time(){
            return this->end_time;
        }

};
class Utils{
    public:
        template<class T>
        void Merge(vector<T> &A,int p,int q,int r,int choice){
            int len_L=q-p+1;
            int len_R=r-q;
            int max=INT_MAX;
            vector<T> L;
            vector<T> R;
            vector<T> res;
            for(int i=0;i<len_L;i++){
                L.push_back(A[p+i]);
            }
            for(int i=0;i<len_R;i++){
                R.push_back(A[q+1+i]);
            }
            Advertisement ad(INT_MAX,INT_MAX,"~","~","~","~");
            L.push_back(ad);
            R.push_back(ad);
            int indexi=0;
            int indexj=0;
            for(int k=p;k<r+1;k++){
                if(Compare(L,R,indexi,indexj,choice)){
                    A[k]=L[indexi];
                    indexi++;
                }else{
                    A[k]=R[indexj];
                    indexj++;
                }
            }
        }

        // "0 for exit,1 for amount,2 for name,3 for email,4 for start_time,5 for end_time"
        template<class T>
        bool Compare(vector<T> &L,vector<T> &R,int l,int r,int choice){
            bool sign=false;
            switch(choice){
                case 1:
                    if(L[l].getAmount()<=R[r].getAmount()){
                        sign=true;
                    }
                    break;
                case 2:
                    if(L[l].getName()<=R[r].getName()){
                        sign=true;
                    }
                    break;
                case 3:
                    if(L[l].getE_mail()<=R[r].getE_mail()){
                        sign=true;
                    }
                    break;
                case 4:
                    if(L[l].getStart_time()<=R[r].getStart_time()){
                        sign=true;
                    }
                    break;
                case 5:
                    if(L[l].getEnd_time()<=R[r].getEnd_time()){
                        sign=true;
                    }
                    break;
            }
            return sign;
        }

        template<class T>
        void Merge_sort_recursive(vector<T> &A,int p,int r,int choice){
            if(p<r){
                int q=(p+r)/2;
                Merge_sort_recursive(A,p,q,choice);
                Merge_sort_recursive(A,q+1,r,choice);
                Merge(A,p,q,r,choice);
            }
        }

        template<class T>
        void Merge_pass(vector<T> &A,int N, int length,int choice)
        { /* 两两归并相邻有序子列 */
            int i, j;
            for ( i=0; i <= N-2*length; i += 2*length ){
                Merge( A, i, i+length-1, i+2*length-1,choice);
            }
            if ( i+length < N ){
                Merge( A, i, i+length-1, N-1,choice);
            } /* 归并最后2个子列*/ 
        }

        template<class T>
        void Merge_sort_non_recursive(vector<T> &A, int N,int choice)
        {
            int length;
            length = 1; 
            while( length < N ) {
                Merge_pass( A,N,length,choice);
                length *= 2;
            }
        }

        int string_to_int(string str){
            stringstream ss;
            int s;
            ss<<str;
            ss>>s;
            return s;
        }//将字符串转换为整数

        void Write_file_solution(string filename,vector<Advertisement> &advertisments){
            int order=1;
            ofstream of(filename);
            for(int i=0;i<advertisments.size();i++){
                of<<"Ad Order:"<<order++<<endl;
                of<<"Ad id:"<<advertisments[i].getId()<<endl;
                of<<"Ad amount:"<<advertisments[i].getAmount()<<endl;
                of<<"Ad name:"<<advertisments[i].getName()<<endl;
                of<<"Ad email:"<<advertisments[i].getE_mail()<<endl;
                of<<"Ad start_time:"<<advertisments[i].getStart_time()<<endl;
                of<<"Ad end_time:"<<advertisments[i].getEnd_time()<<endl;
            }
            of.close();
        }
    //vector<int> &ids,vector<string> &names,vector<int> amounts,vector<string> emails, 
        void Open_file_solution(string filename,vector<Advertisement> &advertisments){
            int i=0;
            int id=1;
            int res;
            vector<int> ids;
            vector<string> names;
            vector<int> amounts;
            vector<string> emails; 
            vector<string> starttime;
            vector<string> endtime;
            ifstream in_file;
            in_file.open(filename);
            string item;
            getline(in_file,item);
            cout<<"The input content in the input.txt file is as follows:"<<endl;
            while(in_file){
                i++;
                res=i%5;
                cout<<i<<" : "<<item<<endl;
                switch(res){
                    case 1:
                        names.push_back(item);
                        break;
                    case 2:
                        amounts.push_back(string_to_int(item));
                        break;
                    case 3:
                        emails.push_back(item);
                        break;
                    case 4:
                        starttime.push_back(item);
                        break;
                    case 0:
                        endtime.push_back(item);
                        break;
                    default:
                        break;
                }
                getline(in_file,item);
            }
            int index=0;
            for(int index=0;index<names.size();index++){
                Advertisement ad(id,amounts[index],names[index],emails[index],starttime[index],endtime[index]);
                advertisments.push_back(ad);
                id++;
            }
            in_file.close();
        }

};


int main(){
    Utils m;
    vector<Advertisement> ads;
    m.Open_file_solution("L://LAB/input.txt",ads);
    int choice;
    cout<<endl;
    cout<<"***************************************************************"<<endl;
    cout<<"please input the way you want to sort the advertisments:\nThe Advertisment has the following attributes:"<<endl;
    cout<<"amount,name,email,start_time,end_time"<<endl;
    cout<<endl;
    cout<<"%%%%%%%%%%%%%%%%%  Welcome to the advertising system  %%%%%%%%%%%%%%%%"<<endl;
    cout<<"***********************  0 for exit        ***************************"<<endl;
    cout<<"***********************  1 for amount      ***************************"<<endl;
    cout<<"***********************  2 for name        ***************************"<<endl;
    cout<<"***********************  3 for email       ***************************"<<endl;
    cout<<"***********************  4 for start_time  ***************************"<<endl;
    cout<<"***********************  5 for end_time    ***************************"<<endl;
    cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
    cout<<"please input your choice: ";
    cin>>choice;
    if(choice!=0){
        m.Merge_sort_recursive(ads,0,ads.size()-1,choice);
        m.Write_file_solution("L://LAB/output.txt",ads);
        cout<<"please observe the results in the txt file: output.txt"<<endl;
    }else{
        cout<<"Exit the system successfully!"<<endl;
    }
    system("pause");
}
