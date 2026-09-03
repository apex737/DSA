#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int N;
int t[55];
/**
 * @example: depend[1] = {3,4}; 1번 업무는 3,4번이 끝나야 시작 가능하다.
 */
vector<int> depend[55]; // depend[u]	=	u가	끝나야 시작할 수 있는	업무들
int indeg[55];          // 선행업무 개수

/**
 * @brief: cc번째에 코코를 쓸 때 소요시간
 * @param: cc: 코코를 적용할 인덱스
 * @return: 완료 시각의	최댓값
 * @example: critical(3): 3번 작업 시간을 절반으로 줄였을 때 소요시간
 */
int critical(int cc)
{
  // 1. 원본 indeg를 수정하지 않기 위해, 복사본을 사용
  vector<int> cpyDeg(N+1);
  for(int i=1; i<=N; i++)
    cpyDeg[i] = indeg[i];

  // 2. indeg가 0인 정점을 큐에 넣기
  queue<int> q;
  for(int i=1; i<=N; i++)
    if(cpyDeg[i]==0) q.push(i);

  vector<int> D(N+1, 0);

  // 3. 위상정렬	루프
  int cnt = 0;
  while(!q.empty())
  {
    int cur = q.front(); q.pop();
    cnt++;

    // D[cur]: cur 번째 업무의 최종 완료시간
    /** @example: depend[1] = {2,3}, depend[2] = {4}, depend[3] = {4}
    *         2 (cost: 5)                   
            /                       
        1 (cost: 2) -- → 4 (cost: 3)               
            \
              3 (cost: 8)                 
              
      D[1] = 2, 
      D[2] = D[1] + 5 = 7, 
      D[3] = D[1] + 8 = 10,
      D[4] = max(D[2], D[3]) + 3 = 13              
   */
    int cost = (cur == cc) ? t[cur]/2 : t[cur];
    D[cur] += cost;

    /** @brief: D-table을 업데이트한다. cur -> nxt 간선(의존성)을 하나씩 제거하고, 전부 제거되면 큐에 넣는다.
     * @param: nxt: cur에 의존하고 있는 인덱스 
     * @param: cpyDeg[nxt]: nxt를 가리키는 정점의 개수
     * @param: D[nxt]: nxt 번째 업무의 최종 완료시간
     * 
     */
    for(int nxt : depend[cur])
    {
      D[nxt] = max(D[nxt], D[cur]);
      cpyDeg[nxt]--;
      if(cpyDeg[nxt]==0) q.push(nxt);
    }
  }

  // 4. 처리한 정점	수 <	N	이면 사이클	→	-1
  if(cnt < N) return -1;
      
  // 5. return max(D[i]);
  int mx = 0;
  for(int i=1; i<=N; i++)
    mx = max(mx, D[i]);
  return mx;
}

void input()
{
  
  for(int i=1; i<=N; i++)
  {
    int M;
    cin >> t[i] >> M;
    while(M--)
    {
      int x; 
      cin >> x;
      depend[x].push_back(i);
      indeg[i]++;
    }
  }
}

void init()
{
  cin >> N;
  for(int i=1; i<=N; i++)
  {
    depend[i].clear();
    indeg[i] = 0;
  }
}

int main()
{
  cin.tie(0)->sync_with_stdio(0);
  int T;
  cin >> T;
  for(int t=1; t<=T; t++)
  {
    init();
    input();
    // 1. cyclic이면 -1 출력
    if(critical(-1) < 0) 
    {
      cout << "#" << t << " " << -1 << "\n";
      continue;
    }

    // 2. cc= 1~N에서 최솟값 출력
    int mn = 1e9;
    for(int i=1; i<=N; i++)
      mn = min(mn, critical(i));
    cout << "#" << t << " " << mn << "\n";
  }

  return 0;
}