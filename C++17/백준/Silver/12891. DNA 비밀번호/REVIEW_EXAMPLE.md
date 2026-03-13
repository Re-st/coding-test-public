# 제목: 메모리 최적화 및 구조 개선 풀이 스케치
- 적용 조건: 현재 풀이와 시간 복잡도는 같지만, O(S) 추가 메모리를 제거하고 싶을 때.
- 핵심 아이디어: 문자열을 정수 배열로 변환하지 않고 직접 사용합니다. 첫 윈도우를 먼저 구성하고, 이후 한 칸씩 슬라이딩하며 개수를 갱신합니다.
- 복잡도: O(S) 시간, O(1) 공간 (문자열 저장 공간 제외)
- 구현 스케치(C++):
int check() {
    // 현재 윈도우의 acgt 배열이 acgtreq 조건을 만족하는지 검사
    if (acgt[0] >= acgtreq[0] && acgt[1] >= acgtreq[1] && acgt[2] >= acgtreq[2] && acgt[3] >= acgtreq[3]) {
        return 1;
    }
    return 0;
}

// ... main 함수 내 ...
// 1. 첫 윈도우(0 ~ p-1) 구성
for (int i = 0; i < p; ++i) {
    // dna[i]에 따라 acgt 배열 갱신
}
int result = check();

// 2. 슬라이딩 (p ~ s-1)
for (int i = p; i < s; ++i) {
    // 이전 문자(dna[i-p]) 제거, 새 문자(dna[i]) 추가
    result += check();
}
cout << result;