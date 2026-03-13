# 제목: std::sort를 이용한 더 깔끔한 풀이
- 적용 조건: C++에서 컨테이너 정렬이 필요할 때 항상 우선적으로 고려해야 합니다.
- 핵심 아이디어: <algorithm> 헤더의 sort 함수와 비교자(greater)를 이용해 내림차순으로 정렬합니다.
- 복잡도: O(L log L)
- 구현 스케치(C++):
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>  // sort
#include <functional> // greater

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string n;
    std::cin >> n;

    // 이 한 줄로 모든 정렬 로직을 대체할 수 있습니다.
    std::sort(n.begin(), n.end(), std::greater<char>());

    std::cout << n;
    return 0;
}