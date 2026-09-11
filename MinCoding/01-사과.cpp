#include <iostream>
#include <vector>

using namespace std;

int N, M;
int board[11][11];
struct Pos {
    int r,c;
};

// 우하좌상
int dc[]={1,0,-1,0};
int dr[]={0,1,0,-1};

/**
 // 내 방향에서 우측이 상대적으로 어떤 좌표인지?
 * @example 내가 오른쪽을 볼때 오른쪽은? 하
 */
int rel_dir[] = { 1, 2, 3, 0 };
vector<Pos> apples(11);

int main()
{
    int T;
    cin >> T;
    for(int t=1; t<=T; t++)
    {
        cin >> N;
        int num = 1;
        for(int i=0; i<N; i++)
            for(int j=0; j<N; j++)
            {
                cin >> board[i][j];
                if(board[i][j] == num) {
                    // apple 숫자를 POS 좌표에 매핑
                    apples[num++] = {i,j}; //
                }
            }
        // 보드에는 1~num-1 까지 수가 들어있다.
        // 1->2, 2->3 ... 를 시뮬레이션하면서 sum 갱신
        int sum = 0;
        int dir = 0;
        Pos cur{0,0}
        for(int i=1; i<num; i++)
        {
            sum += go(cur, apples[i], dir);
        }

        cout << "#" << t << " " << sum << "\n";
    }
    return 0;
}

int go(Pos& st, const Pos& en, int& dir)
/*
1. 어떻게해야 0,0 에서 1이 있는 위치로 갈까? 
=> 인덱스와 방향을 고려하면 1에서 방향이 나온다.
=> 결국 다음으로 넘겨줘야하는 변수는 방향 뿐이란결론..
=> 일반적인 BFS처럼 장애물이 존재하지 않는데, 굳이 그리드를 지나면서 시뮬레이션 해야할까? 
=> 시작 위치와 종료 위치를 알면 다음 dir를 정해주는 걸로 그 위치의 dir를 알수 있다. 
방법은 사분면 논리 

내 위치(st)에서.. en의 위치가..
1사분면에 존재하면? 우회전 1회
2사분면에 존재하면? 우회전 3회
3사분면에 존재하면? 우회전 3회
4사분면에 존재하면? 우회전 2회
같은 열에 존재하면 우회전 0회

선형대수? 좌표변환? 상대위치 LUT??

dir=0; 우; c 증가
dir=1; 하; r 증가
dir=2; 좌; c 감소
dir=3; 상; r 감소

=> 즉, 내가 원점인거다.
dir에 대해 내가 아니라 좌표를 돌린다.
즉 dir이 돌아가면 좌표가 반대로 돌아간거니까 
사실상
r>=0 c>=0은
dir=0일때 1사분면이지만, 
dir=1일때 2사분면,
dir=2일때 3사분면,
dir=3일때 4사분면,

즉 rel_dir[dir]=
r>=0, c>=0

(0,0)->(3,1) dir=0; 왜 1사분면? 나보다 r>=0, c>=0 이라서

문제는 dir이 바뀔때..
(3,1)->(3,2) dir=1; 왜 2사분면? 나보다 r>=3, c<=1 이라서..
일반화하면??
st.r >= en.r && st.c >= en.c 이면 1사분면
 

LUT를 쓰던가, switch/case를 쓰던가..
*/
{
    int turns = 0;
    switch (dir)
    {
    case 0:
        turns += 
        
        break;
    
    default:
        break;
    }



    dir = rel_dir[dir];
    st = en;
    return turns;
}