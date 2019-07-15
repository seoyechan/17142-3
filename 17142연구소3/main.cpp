#include <stdio.h>
#include <queue>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

using namespace std;

int n, m;
int total_virus;
int nfiled[51][51];
int nfiled_copy[51][51];

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

	while (!bfs_q.empty())
	{
		cur_pos = bfs_q.front();
		bfs_q.pop();

		for (int i = 0; i < 4; i++){
			next_pos.x = cur_pos.x + dirx[i];
			next_pos.y = cur_pos.y + diry[i];

			if (next_pos.x >= 0 && next_pos.x < n && next_pos.y >= 0 && next_pos.y < n && nfiled_copy[next_pos.y][next_pos.x] == 0){
				nfiled_copy[next_pos.y][next_pos.x] = 2;
				bfs_q.push(next_pos);
			}
		}
	}
	return 0;
}

int fnCombination(int num, int cnt)
{
	if (cnt == m){
		for (int i = 0; i < m; i++){
			bfs_q.push(selected_virus[i]);
		}
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				nfiled_copy[i][j] = nfiled[i][j];


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
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				scanf("%d", &nfiled[i][j]);
				if (nfiled[i][j] == 2)
				{
					virus[total_virus] = { j, i };
					total_virus++;
				}

			}
		}

		fnCombination(0, 0);





	}
	return 0;
}