#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int* X = new int[1024];
int* Y = new int[1024];

//��ȡ�ļ�
void Open_File(string filename, int& n, int* X, int* Y) { 
	ifstream infile;
	infile.open(filename);
	if (!infile.is_open())//�ж��ļ��Ƿ�ɹ���
	{
		cout << "�ļ�û�ɹ���" << endl;
		exit(1);
	}
	string str;
	getline(infile,str);
	n = stoi(str);

	for (int i = 0; i < n; i++) { 
		if (i == n - 1) {
			getline(infile, str); //��ȡ�����е����һ������
			X[i] = stoi(str);
		}else{
			getline(infile, str,' '); //��ȡ�����е����ݣ��ɿո���
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

//д���ļ�
void write_File(string filename,double res) {
	ofstream outfile;
	outfile.open(filename);
	if (!outfile.is_open())//�ж��ļ��Ƿ�ɹ���
	{
		cout << "�ļ�û�ɹ���" << endl;
		exit(1);
	}
	outfile << res << endl;
}

double Get_Median(int* A, int n) {
	double m = 0;
	if (n % 2 == 0) { //�����������ݸ���Ϊż��
		m = (A[n / 2 - 1] + A[n / 2]) / 2.0; 
	}
	else { //�����������ݸ���Ϊ����
		m = A[n / 2];
	}
	return m;//���ظ���������
}

double Count_Median(int* X, int* Y, int n) { //�������������������λ��
	double x =  Get_Median(X, n);
	double y =  Get_Median(Y, n);
	double z = 0; //zΪ�������������������λ��
	if (n == 1) {	//ֱ�Ӽ�����������ƽ��ֵΪ��λ��
		z = (x + y) / 2;
		return z;
	}else if (n == 2) {
		z = (max(X[0], Y[0]) + min(X[1], Y[1])) / 2;
		return z;
	}
	if (x == y) {
		z = x;
		return z;
	}else if (x < y) {//��ȥX��С��x������ǰ�벿�������Լ�Y�д���y�����к�벿�����ݣ�//�õ��µ�����X1,Y1�������Сn1
		if (n % 2 == 0) { //��nΪż��ʱ
			//����X�����һ��С��x������Y�е�һ������y������������ԭ��������λ����������
			int* X1 = X + n / 2 - 1; //����X1ȡX���±�Ϊn/2-1��������֮��������
			int* Y1 = Y; //����Y1ȡY���±�Ϊ0ֱ���±�Ϊn/2����
			int n1 = n - n / 2 + 1;
			return Count_Median(X1, Y1, n1);
		}else { 
			int* X1 = X + (n - 1) / 2; //����X1ȡX���±�Ϊ(n-1)/2��������֮��������
			int* Y1 = Y; //����Y1ȡY���±�Ϊ0ֱ���±�Ϊ(n-1)/2-1����
			int n1 = n - (n - 1) / 2;
			return Count_Median(X1, Y1, n1);
		}
	}else if (x > y) {//����˼·��������ͬ
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