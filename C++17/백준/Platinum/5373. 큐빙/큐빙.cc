//#define _CRT_SECURE_NO_WARNINGS // 이것도 몰랐었음.freopen에 필요하단 걸.
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
//#include <algorithm>
#include <map>
#include <array>

using namespace std;
typedef pair<int, int> loc;

// U: 윗 면, D: 아랫 면, F: 앞 면, B: 뒷 면, L: 왼쪽 면, R: 오른쪽 면이다
char initFace[6][9] = {
    {'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
    {'y', 'y', 'y', 'y', 'y', 'y', 'y', 'y', 'y'},
    {'r', 'r', 'r', 'r', 'r', 'r', 'r', 'r', 'r'},
    {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'},
    {'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g'},
    {'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'}
};

map<char, int> alphaToFace = {
    {'U', 0}, {'D' , 1}, {'F' , 2}, {'B' , 3}, {'L' , 4}, {'R' , 5}
};// 실수로    'U': 0, 'D' : 1, 'F' : 2, 'B' : 3, 'L' : 4, 'R' : 5 로 함.


map<char, array<int, 8>> alphaToSpiral = {
    {'+', {0, 1, 2, 5, 8, 7, 6, 3}}, {'-', {3, 6, 7, 8, 5, 2, 1, 0} }
};

map<char, array<loc, 12>> outLocs = {
    {'L',
        {
            { // 이 괄호를 놓침. Value 자리에 들어가는 std::array<loc, 12> 역시 내부 배열 초기화를 위해 { ... }로 감싸줘야 합니다.
                {0, 0}, {0, 3}, {0, 6},
                {2, 0} ,{2, 3}, {2, 6},
                {1, 0} ,{1, 3}, {1, 6},
                {3, 8}, {3, 5}, {3, 2}
            }
        }
    },
    {'R',
        {
            {
                {0, 8}, {0, 5}, {0, 2},
                {3, 0}, {3, 3}, {3, 6},
                {1, 8} ,{1, 5}, {1, 2},
                {2, 8} ,{2, 5}, {2, 2},
            }
        }
    },
    {'U',
        {
            {
                {3, 2}, {3, 1}, {3, 0},
                {5, 2}, {5, 1}, {5, 0},
                {2, 2}, {2, 1}, {2, 0},
                {4, 2}, {4, 1}, {4, 0},
            }
        }
    },
    {'D',
        {
            {
                {3, 6}, {3, 7}, {3, 8},
                {4, 6}, {4, 7}, {4, 8},
                {2, 6}, {2, 7}, {2, 8},
                {5, 6}, {5, 7}, {5, 8},
            }
        }
    },
    {'F',
        {
            {
                {0, 6}, {0, 7}, {0, 8},
                {5, 0}, {5, 3}, {5, 6},
                {1, 2} ,{1, 1}, {1, 0},
                {4, 8}, {4, 5}, {4, 2},
            }
        }
    },
    {'B',
        {
            {
                {0, 2}, {0, 1}, {0, 0},
                {4, 0}, {4, 3}, {4, 6},
                {1, 6} ,{1, 7}, {1, 8},
                {5, 8}, {5, 5}, {5, 2},
            }
        }
    },
};

//std::map의 밸류(Value)로 **고정 크기 배열(int[8])**을 직접 사용하는 것은 문법적으로 허용되지 않습니다. 배열은 "복사 가능한 객체"가 아니기 때문입니다.
//map<char, int[8]> alphaToSpiral = {
//    {'+': [0, 1, 2, 5, 8, 7, 6, 3] }, {'-' : [3, 6, 7, 8, 5, 2, 1, 0] }
//};

//map<string, loc[8]> inMatch = {
//    "L-": [{4, 5}, ] ,
//};

char face[6][9];

void changeIn(loc locs[8]) {
    char tmp[2] = { face[locs[6].first][locs[6].second], face[locs[7].first][locs[7].second] };
    for (int i = 7; i >= 2; i--)
        face[locs[i].first][locs[i].second] = face[locs[i - 2].first][locs[i - 2].second];
    for (int i = 0; i < 2; i++)
        face[locs[i].first][locs[i].second] = tmp[i];
}

void changeOutPlus(array<loc, 12> locs) {
    char tmp[3] = { face[locs[9].first][locs[9].second], face[locs[10].first][locs[10].second], face[locs[11].first][locs[11].second] };
    for (int i = 11; i >= 3; i--)
        face[locs[i].first][locs[i].second] = face[locs[i - 3].first][locs[i - 3].second];
    for (int i = 0; i < 3; i++)
        face[locs[i].first][locs[i].second] = tmp[i];
}

void changeOutMinus(array<loc, 12> locs) {
    char tmp[3] = { face[locs[0].first][locs[0].second], face[locs[1].first][locs[1].second], face[locs[2].first][locs[2].second] };
    for (int i = 0; i < 9; i++)
        face[locs[i].first][locs[i].second] = face[locs[i + 3].first][locs[i + 3].second];
    for (int i = 9; i < 12; i++)
        face[locs[i].first][locs[i].second] = tmp[i - 9];
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    //freopen("input.txt", "r", stdin); // 이게 생각이 안남. 
    int n, m;
    cin >> n;
    while (n--) {
        cin >> m;
        memcpy(face, initFace, sizeof(initFace));
        while (m--) {
            string cmd;
            cin >> cmd;
            loc inLocs[8];
            for (int i = 0; i < 8; i++)
                inLocs[i] = { alphaToFace[cmd[0]], alphaToSpiral[cmd[1]][i] }; // 실수로 alphatoSpiral이라 씀.
            changeIn(inLocs);
            if (cmd[1] == '+')
                changeOutPlus(outLocs[cmd[0]]);
            else
                changeOutMinus(outLocs[cmd[0]]);
        }
        for (int i = 0; i < 9; i+=3)
            cout << face[0][i] << face[0][i + 1] << face[0][i + 2] << '\n';
    }
    return 0;
}