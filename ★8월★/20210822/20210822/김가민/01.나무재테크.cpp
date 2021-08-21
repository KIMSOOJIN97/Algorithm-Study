//�ð��ʰ���..
#include <cstring>
#include <vector>
#include<iostream>
#include<list>
using namespace std;
struct Tree 
{
	int r, c, age;
	bool alive;	//����ִ��� ����
};
int N, M, K;
int A[10][10];
int F[10][10];	//�������
list<Tree> Trees;
//�������� ���ǵ� ����
int Dr[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int Dc[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

int solve()
{
	for (int k = 0; k < K; k++)
	{
		//��
		for (list<Tree>::iterator it = Trees.begin(); it != Trees.end(); it++)
		{
			//���̰� ��к��� �۴ٸ�
			if (it->age <= F[it->r][it->c])
			{
				F[it->r][it->c] -= it->age;
				it->age++;
			}
			else
			{
				it->alive = false;
			}
		}
		//����
		for (list<Tree>::iterator it = Trees.begin(); it != Trees.end();)
		{
			if (it->alive)
				it++;
			else
			{
				F[it->r][it->c] += it->age / 2;
				it = Trees.erase(it);
			}
		}
		//����
		for (list<Tree>::iterator it = Trees.begin(); it != Trees.end(); it++)
		{
			if (it->age % 5 == 0)
			{
				for (int i = 0; i < 8; i++)
				{
					int nr = it->r + Dr[i];
					int nc = it->c + Dc[i];
					if (nr<0 || nr>N - 1 || nc<0 || nc>N - 1)
						continue;
					Trees.push_front({ nr, nc, 1, true });

				}
			}
		}
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				F[i][j] += A[i][j];
			}
		}
	}
	//����ִ� ������ ����� ���
	return Trees.size();
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin.tie(NULL);

	cin >> N >> M >> K;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> A[i][j];
			F[i][j] = 5;	//������ ��綥�� ��� �̸� ����
		}
	}
	int x, y, z;
	for (int i = 0; i < M; i++)
	{
		cin >> x >> y >> z;
		//���ʴ�� �־���
		Trees.push_back({ x - 1, y - 1, z, true });
	}
	cout << solve() << "\n";
}