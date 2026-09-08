#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

int N;                       // 지형의 길이
int M;                       // 작업 일수
int MAP[9][9] = {0};         // 맵
int use_map[9][9] = {0};     // 사용하는 맵
int seed_status[9][9] = {0}; // 심어진 작물은 농지가 심어진 횟수 + 4 이상인 경우 수확이 가능해짐
int seed_cul[9][9] = {0};    // 얼마나 경작이 되었는지

int max_ingred = 0;
int total_ingred = 0;

// 현재 로봇의 방향
int now_dir;
// 현재 로봇의 위치
int now_x;
int now_y;

// 로봇 기준 4방위 (상, 우, 하, 좌)
int mov_dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
// 로봇이 바라보는 방향에 따라 고려해 줘야할 방위 선택 배열
int rel_dir[4][4] = {{1, 0, 3, 2}, {2, 1, 0, 3}, {3, 2, 1, 0}, {0, 3, 2, 1}};

int main(int argc, char **argv)
{
  // freopen("input.txt", "r", stdin);

  int test_case;
  int T;
  cin >> T;

  for (test_case = 1; test_case <= T; ++test_case)
  {
    // 초기화
    max_ingred = 0;

    // 입력
    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N; j++)
      {
        cin >> MAP[i][j];
      }
    }
    // 시뮬레이션 계산
    // 시작 위치 지정
    // 모든 위치에서 산은 피해서 시작하자
    // 테두리는 어차피 산이니 고려하지 않겠다.
    for (int i = 1; i < N - 1; i++)
    {
      for (int j = 1; j < N - 1; j++)
      {
        if (MAP[i][j])
          continue;
        // 방향 지정 (0:상, 1:우, 2:하, 3:좌)
        for (int dir = 0; dir < 4; dir++)
        {
          // 맵 초기화, 복사
          memcpy(use_map, MAP, sizeof(MAP));
          // 씨앗 상태 배열 초기화
          memset(seed_status, 0, sizeof(seed_status));
          // 경작 횟수 배열 초기화
          memset(seed_cul, 0, sizeof(seed_cul));
          // 수확된 작물 수 초기화
          total_ingred = 0;
          // 로봇이 이동하면서 갱신되는 방향, 좌표 설정
          now_dir = dir;
          now_x = j;
          now_y = i;

          // 산이 아닐 경우에 심기를 시작하자
          for (int day = 0; day < M; day++)
          {
            // 오전(이동 가능 여부 체크, 가능시 씨 심기, 곡식이 있는 경우 수확
            // 이동 가능 여부 체크
            // 0: 농지, 1: 산인 경우, 2: 싹인 경우, 3: 수확 가능한 경우
            bool possible_move = false;
            for (int four_path = 0; four_path < 4; four_path++)
            {
              if ((use_map[now_y + mov_dir[four_path][0]][now_x + mov_dir[four_path][1]] == 0) || use_map[now_y + mov_dir[four_path][0]][now_x + mov_dir[four_path][1]] == 3)
              {
                possible_move = true;
                break;
              }
            }
            // 씨 심기
            if (possible_move && use_map[now_y][now_x] == 0)
            {
              // 씨앗 심었다고 맵에 표시
              use_map[now_y][now_x] = 2;
              // 경작 경험 1 up
              seed_cul[now_y][now_x]++;
            }
            // 만약 곡식이 있다면?
            if (use_map[now_y][now_x] == 3)
            {
              // 맵 일반 농지로 전환
              use_map[now_y][now_x] = 0;
              // 씨 상태 초기화
              seed_status[now_y][now_x] = 0;
              // 작물 하나 추가
              total_ingred++;
            }

            // 오후(이동)
            //  이동이 가능하다면
            if (possible_move)
            {
              // 바라보는 위치 now_dir기준으로 우측, 앞, 좌측, 뒤 에 있는지 판단
              for (int four_path = 0; four_path < 4; four_path++)
              {
                // 현재 위치 기준으로 어디로 이동이 가능한지 고려를 해야 함
                int dy = mov_dir[rel_dir[now_dir][four_path]][0];
                int dx = mov_dir[rel_dir[now_dir][four_path]][1];

                if (use_map[now_y + dy][now_x + dx] == 0 || use_map[now_y + dy][now_x + dx] == 3)
                {
                  // 이동해야할 곳을 판단하고 어디로 이동해야 할지 판단
                  now_y += dy;
                  now_x += dx;
                  now_dir = rel_dir[now_dir][four_path];
                  break;
                }
              }
            }
            // 새벽 (작물이 자라는것 고려)
            for (int a = 1; a < N - 1; a++)
            {
              for (int b = 1; b < N - 1; b++)
              {
                if (use_map[a][b] == 2)
                {
                  seed_status[a][b]++;
                }
                if (seed_status[a][b] >= seed_cul[a][b] + 4)
                {
                  use_map[a][b] = 3;
                }
              }
            }
          }
          // 최대 최소 정의
          if (total_ingred > max_ingred)
          {
            max_ingred = total_ingred;
          }
        }
      }
    }
    // 출력
    cout << '#' << test_case << ' ' << max_ingred << endl;
  }
  return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}