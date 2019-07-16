#include <stdio.h>
#include <queue>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

using namespace std;

int n, m;
int nRet;
int total_virus;
int total_zero;
int nfiled[51][51];
int nvisit[51][51];

typedef struct pos{
	int x, y;
};

pos virus[51];
pos selected_virus[11];

queue <pos> bfs_q;

int dirx[] = { 0, 0, 1, -1 };
int diry[] = { 1, -1, 0, 0 };

int bfs()
{
	pos cur_pos = { 0, 0 };
	pos next_pos = { 0, 0 };
	int zero = 0;
	int total_time = m;
	int cur_time = 1;
	int queue_last_size = 0;
	int queue_first_size = 0;
	int temp = 0;

	nvisit[next_pos.y][next_pos.x] = 0;

	while (!bfs_q.empty())
	{
		cur_pos = bfs_q.front();
		bfs_q.pop();
		queue_first_size++;

		for (int i = 0; i < 4; i++)
		{
			next_pos.x = cur_pos.x + dirx[i];
			next_pos.y = cur_pos.y + diry[i];

			if (next_pos.x >= 0 && next_pos.x < n && next_pos.y >= 0 && next_pos.y < n && !nvisit[next_pos.y][next_pos.x])
			{
				if (!nfiled[next_pos.y][next_pos.x]){
					nvisit[next_pos.y][next_pos.x] = 1;
					bfs_q.push(next_pos);
					zero++;
					queue_last_size++;
				}
				else if (nfiled[next_pos.y][next_pos.x] == 2 && zero != total_zero){
					nvisit[next_pos.y][next_pos.x] = 1;
					bfs_q.push(next_pos);
					queue_last_size++;
				}
			}
		}

		if (queue_first_size == total_time)
		{
			cur_time++;
			total_time = queue_last_size;
			queue_last_size = 0;
			queue_first_size = 0;
		}
	}

	if (zero == total_zero)		return cur_time - 2;
	else						return -1;

}

int fnCombination(int num, int cnt)
{
	if (cnt == m){
		for (int i = 0; i < m; i++){
			bfs_q.push(selected_virus[i]);
		}

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				nvisit[i][j] = 0;

		int temp_Ret = bfs();

		if (temp_Ret == -1)
			return 0;

		if (temp_Ret < nRet)
			nRet = temp_Ret;

		return 0;
	}

	for (int i = num; i < total_virus; i++){
		selected_virus[cnt] = virus[i];
		fnCombination(i + 1, cnt + 1);
	}
}

int main()
{
	int t;
	int test_case;

	freopen("input.txt", "r", stdin);

	scanf("%d", &t);
	for (test_case = 1; test_case <= t; ++test_case)
	{
		scanf("%d %d", &n, &m);
		total_virus = 0;
		total_zero = 0;
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				scanf("%d", &nfiled[i][j]);
				if (nfiled[i][j] == 2)
				{
					virus[total_virus] = { j, i };
					total_virus++;
				}
				else if (nfiled[i][j] == 0)
				{
					total_zero++;
				}

			}
		}

		nRet = 987654321;
		if (total_zero != 0)
			fnCombination(0, 0);
		else
			nRet = 0;

		if (nRet == 987654321)
			nRet = -1;

		printf("%d\n", nRet);



	}
	return 0;
}