#include <vector>
#include <iostream>
#include <exception>

using namespace std;

vector<pair<int, int>> Q2(int N, int M)
{
	/* ������ 2 */
	if( N < 1 || M < 1 || N < M) throw exception();
	// return struct
	vector<pair<int, int>> res;
	// ���������� ��������� � ������ � ����� �������� ��������
	int residue_right = int((N % M) / 2);
	int residue_left = (N % M) - residue_right;
	// ������� ����� �������
	if(residue_left > 0)
		res.push_back(pair<int, int>(0, residue_left-1));
	// ������������� �������
	int cnt = (N - N % M) / M;
	for(int n = 0; n < cnt; n++)
		res.push_back(pair<int, int>(residue_left + M * n, residue_left + M * (n + 1) -1));
	// ������� ������ �������
	if(residue_right > 0)
		res.push_back(pair<int, int>(N-residue_right, N-1));
	return res;
}

int main()
{
    cout << endl << "Question #2" << endl;
	int M = 7, N = 2;
	vector<pair<int, int>> r2 = Q2(M, N);
	int n = 1;
	cout << "M = " << M << ", N = " << N << endl;
	for(auto i = r2.begin(); i != r2.end(); (++i, ++n))
		cout << n << ": " << i->first << ", " << i->second << endl;
	return 0;
}