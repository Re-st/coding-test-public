# 제목: 더 간결하고 안전한 매개 변수 탐색 구현
- 적용 조건: 현재 풀이와 알고리즘은 동일하나, 구현을 더 명확하고 안전하게 만들고 싶을 때.
- 핵심 아이디어: 이진 탐색의 하한선은 `maxClip`만으로 충분하며, `fits` 함수는 필요한 블루레이 개수를 직접 세는 방식으로 구현하면 훨씬 직관적입니다.
- 복잡도: O(N * log(S)) (동일)
- 구현 스케치(C++):
bool fits(int mSize, int M, const vector<int>& lectures) {
    int count = 1, current_sum = 0;
    for (int len : lectures) {
        // 단일 강의가 용량을 초과하는 경우는 low 경계에서 이미 필터링됨
        if (current_sum + len > mSize) {
            count++;
            current_sum = len;
        } else {
            current_sum += len;
        }
    }
    return count <= M;
}

// main 함수 내 이진 탐색 부분
int mMin = maxClip, mMax = total;
while (mMin < mMax) {
    int middle = mMin + (mMax - mMin) / 2;
    if (fits(middle, m, is)) {
        mMax = middle;
    } else {
        mMin = middle + 1;
    }
}
cout << mMin;