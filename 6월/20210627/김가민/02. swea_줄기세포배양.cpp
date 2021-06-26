https://kbj96.tistory.com/20

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;
const int dx[] = { -1, 0, 1, 0 };
const int dy[] = { 0, 1, 0, -1 };
const int MAX = 1000;
int mid = MAX / 2;
int map[MAX][MAX];
int n, m, k;
struct Node
{
	int x, y;
	int time;	
	int type;	//�����
	Node(int xx, int yy, int t, int tp)
	{
		x = xx;
		y = yy;
		time = t;
		type = tp;
	}

	bool operator < (const Node& nd)const	//����� ��ġ�� ���� �ٱ⼼�� ���� ó��
	{
		return type < nd.type;
	}
};


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int T, test_case=0;
	ifstream cin;
	cin.open("input.txt");


	cin >> T;
	
	for (int test_case = 1; test_case <= T; test_case++)
	{
		cin >> n >> m >> k;
		queue<Node> disable_Q;	//��Ȱ�������� �ٱ⼼��
		priority_queue<Node> ableQ;	//Ȱ�������� �ٱ⼼��
		memset(map, 0, sizeof(map));
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				cin >> map[i + mid][j + mid];
				if (map[i + mid][j + mid] == 0)
					continue;
				else
				{
					disable_Q.push(Node(i + mid, j + mid, map[i + mid][j + mid], map[i + mid][j + mid]));
				}
			}
		}
		queue<Node> t_disableQ;
		priority_queue<Node>t_ableQ;
		for (int cnt = 1; cnt <= k; cnt++)
		{
			//Ȱ�� -> ��Ȱ��
			while (!ableQ.empty())
			{
				Node nt = ableQ.top();
				ableQ.pop();
				int tt = nt.time;
				for (int dir = 0; dir < 4; dir++)
				{
					int nx = nt.x + dx[dir];
					int ny = nt.y + dy[dir];
					if (map[nx][ny] != 0)
						continue;
					map[nx][ny] = nt.type;
					t_disableQ.push(Node(nt.x, nt.y, nt.type, nt.type));
				}
				if ((tt + 1) != nt.time)
					t_ableQ.push(Node(nt.x, nt.y, tt + 1, nt.type));

			}

			//��Ȱ�� -> Ȱ��
			while (!disable_Q.empty())
			{
				Node t = disable_Q.front();
				int tt = t.time;
				disable_Q.pop();
				tt--;
				if (tt == 0)
				{
					ableQ.push(Node(t.x, t.y, tt, t.type));
				}
				else
					t_disableQ.push(Node(t.x, t.y, tt, t.type));
			}
			while (!t_disableQ.empty())
			{
				disable_Q.push(t_disableQ.front());
				t_disableQ.pop();
			}
			while(!t_ableQ.empty())
			{
				ableQ.push(Node(t_ableQ.top()));
				t_ableQ.pop();
			}
		}

		int ans = 0;
		while (!ableQ.empty())
		{
			ans += 1;
			ableQ.pop();
		}
		while (!disable_Q.empty())
		{
			ans += 1;
			disable_Q.pop();
		}

		cout << "#" << test_case << ' ' << ans << "\n";

	}

	return 0;
}
