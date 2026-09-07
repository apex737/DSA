#include <bits/stdc++.h>
using namespace std;
int N, M;
int g[12][12];
//	0=농지,	1=산
int dr[4] = {-1, 0, 1, 0}; //	상	우	하	좌	(시계방향)
int dc[4] = {0, 1, 0, -1};
int cropDay[12][12];
int sprouts[12][12];
//	이	칸의	곡식이	열리는	날	(0이면	아무것도	안	자람)
//	이	칸에서	지금까지	싹이	난	횟수	K
//	day일에	(r,c)로	이동할	수	있는가?
bool movable(int r, int c, int day)
{
  //	TODO	①:	범위	밖	/	산	→	불가
  //	TODO	②:	아무것도	안	자람	→	빈	농지	→	가능
  //	TODO	③:	자라는	중인데	아직	곡식이	안	열림	→	불가
  //
  return false;
}
int simulate(int sr, int sc, int sf)
{
  //	TODO	④:	cropDay,	sprouts	초기화	(시뮬레이션마다!)
  for (int day = 1; day <= M; day++)
  {
    //	TODO	⑤	오전:
    //
    //
    //
    //	TODO	⑥	오후:
    //
    //
  }
  return /*	수확	횟수	*/ 0;
}

int main()
{
  int T;
  scanf("%d", &T);
  for (int tc = 1; tc <= T; tc++)
  {
    scanf("%d	%d", &N, &M);
    //	TODO	⑦:	지형	입력
    //	TODO	⑧:	모든	농지	칸	×	4방향에	대해	simulate	하고	최댓값	출력
  }
  return 0;
}