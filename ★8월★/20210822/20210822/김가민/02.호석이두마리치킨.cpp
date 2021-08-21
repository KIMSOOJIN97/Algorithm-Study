#include <cstring>
#include <vector>
#include<iostream>
using namespace std;
//�÷��̵� �ͼ��� �ִܰŸ��� ���ϰ� ��� ������ 2�� ������ ���� �պ��Ÿ��� ã�´�.
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin.tie(NULL);

	int N, M;
	int map[101][101];
	cin >> N >> M;
	//�迭 �ʱ�ȭ
	memset(&map, 10000, sizeof(map));

	for (int i = 1; i <= M; i++)
	{
		int a, b;
		cin >> a >> b;
		//������üũ
		map[a][b] = map[b][a] = 1;
	}
	//�÷��̵� �ͼ��� �ִܰŸ� ���ϱ�
	for (int k = 1; k <= N; k++)
	{
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				//��尡 ���� ���� 0���� ����
				if (i == j)
					map[i][j] = 0;
				map[i][j] = min(map[i][j], map[i][k] + map[k][j]);
			}
		}
	}
	//��� ������ ������ ���� �պ��Ÿ� ã��
	int sum = 0;
	int a, b, c;
	c = 10000;
	for (int i = 1; i < N; i++)
	{
		for (int j = i + 1; j <= N; j++)
		{
			sum = 0;
			for (int k = 1; k <= N; k++)
			{
				//�պ��Ÿ�
				sum += min(map[k][i], map[k][j]) * 2;
			}
			if (sum <= c)
			{
				//a,b,c�� ������Ʈ ������
				if ((i <= a && j < b) || (sum < c))
				{
					a = i;
					b = j;
					c = sum;
				}
			}
		}
	}
	cout << a << ' ' << b << ' ' << c;
}