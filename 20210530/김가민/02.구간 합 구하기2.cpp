#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;
typedef long long ll;

ll init(vector<ll>& arr, vector<ll>& tree, int node, int l, int r)
{
	if (l == r)
		return tree[node] = arr[l];
	int mid = (l + r) / 2;
	return tree[node] = init(arr, tree, node * 2, l, mid) + init(arr, tree, node * 2 + 1, mid + 1, r);
}

void updateLazy(vector<ll>& tree, vector<ll>& lazy, int node, int l, int r)
{
	if (lazy[node] == 0)
		return;

	//�ڽĳ�尡 �ִ� �� ��ŭ lazy���� ���Ͽ� ����.
	tree[node] += (r - l + 1) * lazy[node];

	//leaf�� �ƴϸ� �ڽĿ��� lazy�� ������
	if (l != r)
	{
		lazy[node * 2] += lazy[node];
		lazy[node * 2 + 1] += lazy[node];
	}

	//������ �� lazy�� �ʱ�ȭ
	lazy[node] = 0;
}

void update(vector<ll>& tree, vector<ll>& lazy, int node, int l, int r, int start, int end, ll val)
{
	//lazy�ִ��� Ȯ���� lazy�� ������ ������Ʈ
	updateLazy(tree, lazy, node, l, r);

	//1. �������� ������ �ʴ´ٸ� return
	if (start > r || end < l)
		return;
	//2. �������� ���ϴ� ��� 
	if (start <= l && r <= end)
	{
		//�θ��带 �ڽĳ�尡 �ִ� ����ŭ val�� ���ؼ� ������
		tree[node] += (r - l + 1) * val;

		//�������� �������� l�� r�� �ٸ� ���
		if (l != r)
		{
			//lazy���� val�� ������(lazy�� ������Ʈ)
			lazy[node * 2] += val;
			lazy[node * 2 + 1] += val;
		}
		return;
	}
	//3. ������ ������ �ִ°�� mid�� ����Ͽ� �ɰ�
	int mid = (l + r) / 2;
	update(tree, lazy, node * 2, l, mid, start, end, val);
	update(tree, lazy, node * 2 + 1, mid + 1, r, start, end, val);
	//�θ��� ������Ʈ
	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

ll sum(vector<ll>& tree, vector<ll>& lazy, int node, int l, int r, int start, int end)
{
	//update ���� lazy�� �й�(lazy ������)
	updateLazy(tree, lazy, node, l, r);

	if (start > r || end < l)
		return 0;
	if (start <= l && r <= end)
		return tree[node];
	int mid = (l + r) / 2;
	return sum(tree, lazy, node * 2, l, mid, start, end) + sum(tree, lazy, node * 2 + 1, mid + 1, r, start, end);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, m, k;
	cin >> n >> m >> k;

	int h = (int)ceil(log2(n));
	int tree_size = (1 << (1 + h));
	vector<ll> arr(n);
	vector<ll> tree(tree_size);
	vector<ll> lazy(tree_size);

	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}

	init(arr, tree, 1, 0, n - 1);
	for (int i = 0; i < m + k; i++)
	{
		int num;
		cin >> num;
		if (num == 1)
		{
			int start, end;
			ll val;
			cin >> start >> end >> val;
			update(tree, lazy, 1, 0, n - 1, start - 1, end - 1, val);
		}
		else if (num == 2)
		{
			int start, end;
			cin >> start >> end;
			cout << sum(tree, lazy, 1, 0, n - 1, start - 1, end - 1) << "\n";
		}
	}
	return 0;
}