#include <vector>
#include <iostream>
#include <exception>

using namespace std;

vector<vector<int>> Q1(int N)
{
	/*
	������ 1
	������� ���������� ����������� ����� �� N ������������ � ������������� ������ ����� �� ������� ���������. 
	*/
	if( N < 1) throw exception();
	// result 
	vector<vector<int>> res;
	// simple numbers
	vector<int> simple_num(1, 2);
	// N = 1
	res.push_back(vector<int>(1, 1));
	// N = 2
	res.push_back(vector<int>(2));
	res[1][0] = 1;
	res[1][1] = 2;
	// N > 2
	for(int n = 3; n <= N; n++)
	{
		// ������ ����� �������� �� 1
		res.push_back(vector<int>(1, 1));
		// �������
		int nd = n;
		// �������
		for(auto last_divisor = simple_num.begin(); last_divisor != simple_num.end(); )
		{
			if( nd % *last_divisor == 0){
				nd = nd / *last_divisor;
				res[n-1].push_back(*last_divisor);
			}
			else
				++last_divisor;
		}
		// ���� n �������
		if(res[n-1].size() == 1){
			simple_num.push_back(n);
			res[n-1].push_back(n);
		}
	}
	return res;
}

int main()
{
	cout << "Question #1" << endl;
	vector<vector<int>> r1 = Q1(11);
	int n = 1;
	for(auto i = r1.begin(); i != r1.end(); (++i, ++n)){
		cout << n << ": ";
		for(auto j = (*i).begin(); j != (*i).end(); ++j)
			cout << *j << " ";
		cout << endl;
	}
	return 0;
}