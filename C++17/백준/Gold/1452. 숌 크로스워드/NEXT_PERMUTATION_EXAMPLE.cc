#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // 예시 1: 숫자 벡터
    vector<int> nums = {1, 2, 3};
    
    cout << "=== 숫자 벡터 예시 ===" << endl;
    do {
        for (int x : nums) {
            cout << x << " ";
        }
        cout << endl;
    } while (next_permutation(nums.begin(), nums.end()));
    
    cout << "\n=== 문자열 벡터 예시 ===" << endl;
    
    // 예시 2: 문자열 벡터 (우리 코드와 동일)
    vector<string> words = {"abc", "def", "ghi"};
    
    cout << "초기 순서: ";
    for (string w : words) cout << w << " ";
    cout << "\n\n";
    
    int count = 0;
    do {
        count++;
        cout << count << "번째 순열: ";
        for (string w : words) {
            cout << w << " ";
        }
        cout << endl;
    } while (next_permutation(words.begin(), words.end()));
    
    cout << "\n총 " << count << "가지 순열이 있습니다.\n";
    
    cout << "\n=== 4개 단어 예시 ===" << endl;
    vector<string> words4 = {"a", "b", "c", "d"};
    count = 0;
    do {
        count++;
        if (count <= 5 || count > 20) {  // 처음 5개와 마지막 5개만 출력
            cout << count << ": ";
            for (string w : words4) cout << w << " ";
            cout << endl;
        }
    } while (next_permutation(words4.begin(), words4.end()));
    
    cout << "... (중간 생략) ...\n";
    cout << "총 " << count << "가지 순열 (4! = 24)\n";
    
    return 0;
}
