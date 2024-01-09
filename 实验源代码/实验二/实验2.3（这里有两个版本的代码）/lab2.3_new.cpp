#include<iostream>
#include<string>
#include<stack>
#include<cstdlib> 
#include<sstream> 
#include<vector>
#include<stdio.h>
#include<malloc.h>
#include <stdlib.h>
using namespace std; 

int string_to_int(string str);
int judge(string a);
vector<string> init_data(string s);
int caclulate_Postfix(vector<string> s);
vector<string>  Infix_to_Postfix(vector<string> s);
void Print_Postfix(vector<string> s);

int string_to_int(string str){
	stringstream ss;
	int s;
	ss<<str;
	ss>>s;
	return s;
}//将字符串转换为整数

int judge(string a){
	if(a=="+"||a=="-")	
		return 1;
	else if(a=="*"||a=="/")  
		return 2;
	else if(a=="(")	
		return 3;
	else if(a==")")	
		return -1;
	else 
		return 0;
}//将数字的优先级定做0，运算符号大于0，便于后续处理

vector<string> init_data(string s){//初始化 
	vector<string>a;
	int j,i;//定义两个快慢指针
	i=0;
	while(i<s.size())
	{	
        j=i;//快指针j的初始位置为慢指针i上一次循环遍历的位置，若循环刚开始则i=j=0
		
		while(j<s.size()&&s.at(j)<='9'&&s.at(j)>='0'){
			j++;
		}//当j所指向的字符均是数字时，快指针j增加1
		if(i==j){
			a.push_back(s.substr(i,1));
			i=i+1;
		}//走到这里则表明没有进入上面的while循环，则i和j指向的位置为非数字，可能是符号
		else{
			a.push_back(s.substr(i,j-i));
			i=j;
		}//将多个位数的数字存储	
	}
	return a;//返回整理好的字符串
}


int caclulate_Postfix(vector<string> s){
	stack<int> result;
	int temp1,temp2;
	for(int i=0; i<s.size();i++){
		
		if(judge(s[i])==0)
			result.push(string_to_int(s[i]));
		else{
			temp1=result.top();
			result.pop();
			temp2=result.top();
			result.pop();
			if(s[i]=="+")
				result.push(temp2+temp1);
							
			if(s[i]=="-")
				result.push(temp2-temp1);
							
			if(s[i]=="*")
				result.push(temp2*temp1);
							
			if(s[i]=="/")
				result.push(temp2/temp1);
		}	
		
	}
	return result.top();
}

vector<string>  Infix_to_Postfix(vector<string> s){
	stack<string> result;
	vector<string> save;
	for(int i=0; i<s.size();i++){
		
		if(judge(s[i])==0)//遇到数字就直接输出
			save.push_back(s[i]);
			
		if(judge(s[i])>0){//如果不是数字
			
			if(result.empty())//栈为空则直接压栈 
				result.push(s[i]);
			
			else{
				
				if(judge(s[i])>judge(result.top()))//操作符优先级比栈顶操作符优先级高
				{	
                    result.push(s[i]);
				}	
				
				else{
					while((!result.empty())&&judge(result.top())>=judge(s[i])&&result.top()!="(")//弹栈并输出直到栈为空或遇到优先级更低的操作符 (除了左括号)
					{	
						save.push_back(result.top());
						result.pop();
					}
					result.push(s[i]);
				}
				
			}
			
		}
		
		if(judge(s[i])==-1){//如果遇到右括号，则全部输出括号里面的符号
			while(result.top()!="("){
				save.push_back(result.top());
				result.pop();
			}
			result.pop();			
		}
	}
	
	while(!result.empty()){//若此时栈仍然为空则输出所有的符号
		save.push_back(result.top());
		result.pop();
	}

	return save;
	
	 
}

void Print_Postfix(vector<string> s){
    vector<string> res(s);
    for(int index=0;index<res.size();index++){
        if(index==res.size()-1){
            cout<<res[index]<<endl;
        }else{
            cout<<res[index]<<",";
        }
        
    }
}



int main(){
	int n;
	string input;
	vector<string> str_init,str_postfix;
    cout<<"please input the number of the expressions you are about to input:"<<endl;
	cin>>n;
    int sum=n;
	while(n--){
        cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
        cout<<"please input the expressions:"<<endl;
		cin>>input;
        cout<<"The "<<sum-n<<" th infix-expression you entered is:"<<endl;
        cout<<input<<endl;

		str_init=init_data(input);

		str_postfix=Infix_to_Postfix(str_init);
        cout<<"The "<<sum-n<<" th postfix-expression you entered is:"<<endl;
        Print_Postfix(str_postfix);

        cout<<"The expression you entered evaluates to:"<<endl;
		cout<<caclulate_Postfix(str_postfix)<<endl; 
	}
	system("pause");
}
