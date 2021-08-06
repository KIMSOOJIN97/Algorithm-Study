#include<iostream>
#include<algorithm>
#include<vector>
#include<math.h>
#include<cstring>
#include<fstream>
using namespace std;
//���漱�� �����¿�� ���� �ְ� �� ������� L, R�� �������� �����ϱ� ������ 
//DFS�� ��Ž�ϸ鼭 �� ����� �����Ѵ�.
int N, L, R, cnt = 0, sum = 0;
int map[51][51];	//n*nũ���� ��
vector<pair<int, int>> vec;	//���� �� �α��� ������ ���� ������ ������ ��ġ�� ���� ����(��, ��)
bool checked[51][51]; //�� ������ ���տ��� üũ�� �迭 
//�� �� �� ��
int dr[4] = { 1, -1, 0, 0 };
int dc[4] = { 0, 0, -1, 1 };

void DFS(int row, int col)
{
	//4�������� Ž���ϸ鼭 DFS�� ����
	for (int i = 0; i < 4; i++)
	{
		int sr = row + dr[i];
		int sc = col + dc[i];

		//�ش� ��ġ�� �湮���� �ʾҰ� �γ����� �α����̰� L�̻� R�̸��̸�
		//sum �� �γ����� �α����� ������ �� ������ ����+1 ��Ų��.
		//�Ŀ� ������ ������ �α����� ������Ʈ �����ֱ� ���� vec�� �ش糪���� ��ġ(��, ��)�� �ִ´�.
		if (!checked[sr][sc])
		{
			if (0 <= sr && sr < N && 0 <= sc && sc < N)
			{
				int val = abs(map[row][col] - map[sr][sc]);
				if (L <= val && val <= R)
				{
					checked[sr][sc] = true;
					sum += map[sr][sc];
					cnt++;
					vec.push_back(make_pair(sr, sc));
					DFS(sr, sc);
				}
			}
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int ans = 0, avg = 0;
	cin >> N >> L >> R;

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			cin >> map[i][j];
		}
	}
	
	while (1)
	{
		//flag, üũ�迭 �ʱ�ȭ
		bool flag = false;
		memset(checked, false, sizeof(checked));
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				//�湮���� �ʾҴٸ�
				if (!checked[i][j])
				{
					//vec, cnt, sum, üũ�迭 �ʱ�ȭ
					vec.clear();
					cnt = 1;
					sum = map[i][j];
					checked[i][j] = true;
					//�α��̵��� ���� ó�� �Է¹��� ������ ��ġ�� ���Ϳ� �ְ� DFS�� ����
					vec.push_back(make_pair(i, j));
					DFS(i, j);
					//������ ���� 2�̻��̸� avg���� ���ϰ� ������ ������ �α����� avg�� ������Ʈ��Ŵ
					if (cnt >= 2)
					{
						flag = true;
						avg = sum / cnt;
						for (int k = 0; k < vec.size(); k++)
						{
							map[vec[k].first][vec[k].second] = avg;
						}
					}
				}
			}
		}
		if (!flag)
			break;
		else
			ans++;
	}
	cout << ans << "\n";
	return 0;
}