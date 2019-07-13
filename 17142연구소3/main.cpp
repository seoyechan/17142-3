#include <stdio.h>
#include <queue>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

using namespace std;

int n, m;
int total_virus;
int nfiled[51][51];

typedef struct pos{
	int x, y;
};

pos virus[51];
pos selected_virus[11];




int fnCombination(int num, int cnt)
{
	if (cnt == m){

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