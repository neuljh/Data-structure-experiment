#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int* X = new int[1024];
int* Y = new int[1024];

//读取文件
void Open_File(string filename, int& n, int* X, int* Y) { 
	ifstream infile;
	infile.open(filename);
	if (!infile.is_open())//判断文件是否成功打开
	{
		cout << "文件没成功打开" << endl;
		exit(1);
	}
	string str;
	getline(infile,str);
	n = stoi(str);

	for (int i = 0; i < n; i++) { 
		if (i == n - 1) {
			getline(infile, str); //获取数组中的最后一个数据
			X[i] = stoi(str);
		}else{
			getline(infile, str,' '); //获取数组中的数据，由空格间隔
			X[i]= stoi(str);
		}
	}
	for (int i = 0; i < n; i++) {
		if (i == n - 1) {
			getline(infile, str); 
			Y[i] = stoi(str);
		}
		else {
			getline(infile, str, ' ');
			Y[i] = stoi(str);
		}
	}
	infile.close();
}

//写入文件
void write_File(string filename,double res) {
	ofstream outfile;
	outfile.open(filename);
	if (!outfile.is_open())//判断文件是否成功打开
	{
		cout << "文件没成功打开" << endl;
		exit(1);
	}
	outfile << res << endl;
}

double Get_Median(int* A, int n) {
	double m = 0;
	if (n % 2 == 0) { //若数组中数据个数为偶数
		m = (A[n / 2 - 1] + A[n / 2]) / 2.0; 
	}
	else { //若数组中数据个数为奇数
		m = A[n / 2];
	}
	return m;//返回浮点数类型
}

double Count_Median(int* X, int* Y, int n) { //计算两个有序数组的中位数
	double x =  Get_Median(X, n);
	double y =  Get_Median(Y, n);
	double z = 0; //z为最终两个有序数组的中位数
	if (n == 1) {	//直接计算两个数的平均值为中位数
		z = (x + y) / 2;
		return z;
	}else if (n == 2) {
		z = (max(X[0], Y[0]) + min(X[1], Y[1])) / 2;
		return z;
	}
	if (x == y) {
		z = x;
		return z;
	}else if (x < y) {//舍去X中小于x的所有前半部分数据以及Y中大于y的所有后半部分数据，//得到新的数组X1,Y1和数组大小n1
		if (n % 2 == 0) { //当n为偶数时
			//保留X中最后一个小于x的数和Y中第一个大于y的数，即保留原来计算中位数的两个数
			int* X1 = X + n / 2 - 1; //数组X1取X的下标为n/2-1的数及其之后所有数
			int* Y1 = Y; //数组Y1取Y中下标为0直到下标为n/2的数
			int n1 = n - n / 2 + 1;
			return Count_Median(X1, Y1, n1);
		}else { 
			int* X1 = X + (n - 1) / 2; //数组X1取X的下标为(n-1)/2的数及其之后所有数
			int* Y1 = Y; //数组Y1取Y中下标为0直到下标为(n-1)/2-1的数
			int n1 = n - (n - 1) / 2;
			return Count_Median(X1, Y1, n1);
		}
	}else if (x > y) {//操作思路和上述相同
		if (n % 2 == 0) {
			int* X2 = X;
			int* Y2 = Y + n / 2 - 1; 
			int n2 = n - n / 2 + 1;
			return Count_Median(X2, Y2, n2);
		}else {
			int* X2 = X;
			int* Y2 = Y + (n - 1) / 2;
			int n2 = n - (n - 1) / 2;
			return Count_Median(X2, Y2, n2);
		}
	}
	return -1;
}

int main() {
	int n;
	string infilename, outfilename;
	infilename = "L://LAB/input_lab3.1.txt";
	outfilename = "L://LAB/output_lab3.1.txt";
	Open_File(infilename, n, X, Y);
	double res = Count_Median(X, Y, n);
	write_File(outfilename, res);
	cout<<"The result is: "<<res<<endl;
	system("pause");
}