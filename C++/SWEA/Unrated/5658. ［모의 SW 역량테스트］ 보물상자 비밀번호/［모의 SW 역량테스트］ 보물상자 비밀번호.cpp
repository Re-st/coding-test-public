#include<iostream>
#include<vector>
#include<set>
#include<algorithm>

using namespace std;

vector<int> digit;

int read_number(int start, int end) {
	int ans = 0;
	for (int i = start; i < end - 1; i++) {
		ans += digit[i];
		ans *= 16;
	}
	return ans + digit[end - 1];
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	/*
	   아래의 freopen 함수는 input.txt 를 read only 형식으로 연 후,
	   앞으로 표준 입력(키보드) 대신 input.txt 파일로부터 읽어오겠다는 의미의 코드입니다.
	   //여러분이 작성한 코드를 테스트 할 때, 편의를 위해서 input.txt에 입력을 저장한 후,
	   freopen 함수를 이용하면 이후 cin 을 수행할 때 표준 입력 대신 파일로부터 입력을 받아올 수 있습니다.
	   따라서 테스트를 수행할 때에는 아래 주석을 지우고 이 함수를 사용하셔도 좋습니다.
	   freopen 함수를 사용하기 위해서는 #include <cstdio>, 혹은 #include <stdio.h> 가 필요합니다.
	   단, 채점을 위해 코드를 제출하실 때에는 반드시 freopen 함수를 지우거나 주석 처리 하셔야 합니다.
	*/
	//freopen("input.txt", "r", stdin);
	cin >> T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for (test_case = 1; test_case <= T; ++test_case)
	{
		int N, K; char tmp;
		cin >> N >> K;
		digit.resize(N);
		for (int i = 0; i < N; i++) {
			cin >> tmp;
			if (tmp >= 'A') digit[i] = 10 + tmp - 'A';
			else digit[i] = tmp - '0';
		}
		static set<int> numbers;
		numbers.clear();
		for (int i = 0; i < N / 4; i++) {
			rotate(digit.begin(), digit.begin() + 1, digit.end());
			for (int j = 0; j < 4; j++)
				numbers.emplace(read_number(j * (N / 4), (j + 1) * (N / 4)));
		}
		// set의 정렬순서를 반대로 할수는 없나? (큰것부터 혹은 custom operator<)
		auto it = numbers.end();
		for (int i = 0; i < K; i++)
			it = prev(it);
		printf("#%d %d\n", test_case, *it);
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
			 이 부분에 여러분의 알고리즘 구현이 들어갑니다.
		 */
		 /////////////////////////////////////////////////////////////////////////////////////////////


	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}