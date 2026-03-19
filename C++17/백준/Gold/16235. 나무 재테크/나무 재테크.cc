#include <iostream>
#include <deque>
#include <cstring>
#include <algorithm>

using namespace std;

int n, m, k;
struct Tree {
    int r, c, age;
    Tree(int r, int c, int age) : r(r), c(c), age(age) {} // 초기화 리스트 방식. 이거를 까먹음. 잘 기억하자.
    // < 연산자를 정의하여 age 기준 오름차순 정렬 조건을 만듭니다. 이것도 잘 기억하자.
    // 혹은 sort(field[i][j].begin(), field[i][j].end(), [](const Tree& a, const Tree& b) { return a.age < b.age; });
    /*bool operator<(const Tree& other) const {
        return this->age < other.age;
    }*/
};
// tuple 쓰려다가. get<0>니 뭐니 거추장스러워서 struct로 바꿈. 앞으로도 struct를 잘 활용하자.

deque<int> field[10][10];
deque<Tree> deadtrees;
int food[10][10];
int dFood[10][10];

void spring() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            deque<int> tmp;
            for (int age: field[i][j])
                if (food[i][j] >= age) {
                    food[i][j] -= age;
                    tmp.push_back(age + 1);
                }
                else {
                    //cout << food[i][j] << ' ' << age;
                    deadtrees.push_back(Tree(i, j, age));
                }
            // 여기서 기존 field i j 는 잘 지워지는거 맞나? memory 문제 없겠지?
            // tmp 는 local변수인데 이렇게하면 잘 복사되는건가? ptr만 옮기는거면 문제생길텐데.
            // field[i][j].clear();
            field[i][j] = tmp;
        }
}

void summer() {
    for (Tree deadtree : deadtrees) {
        food[deadtree.r][deadtree.c] += deadtree.age / 2;
    }
    deadtrees.clear();
}

void autumn() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int age : field[i][j])
                if (age % 5 == 0) {
                    for (int di: {-1, 0, 1}) {
                        int newi = i + di;
                        if (newi == -1 or newi == n)
                            continue;
                        for (int dj: { -1, 0, 1 }) {
                            if (not di and not dj)
                                continue;
                            int newj = j + dj;
                            if (newj == -1 or newj == n)
                                continue;
                            // vector였다면 올바른 방식: v.insert(v.begin(), value);. 내 실수: (0, value);
                            field[newi][newj].push_front(1);

                        }
                    }
                }
}

void winter() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            food[i][j] += dFood[i][j];
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> dFood[i][j];
    while (m--) {
        int x, y, z;
        cin >> x >> y >> z;
        field[x - 1][y - 1].push_back(z);
    }
    // vector의 print가 있나? Tree에 print를 만들수 있나? 기본.. 내가 뭔말하는지 알지?
    //cout << field[0][0].front().age;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            sort(field[i][j].begin(), field[i][j].end());
    //memset(food, 5, sizeof(food));
    //memset은 메모리를 1바이트(byte) 단위로 채웁니다.
    fill(food[0], food[0] + 10 * 10, 5);
    // food도 안됨. int[10] 배열 100개르 뛰어넘을 수 있음. food[0]이나 &food[0][0]해야 됨.
    while (k--) {
        spring();
        summer();
        autumn();
        winter();
    }
    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            ans += field[i][j].size();
    cout << ans;
    return 0;
}