import os
import sys
from openai import OpenAI

client = OpenAI(api_key=os.environ["OPENAI_API_KEY"])


PROMPT_CPP = """
# 삼성 SW 역량테스트 합격 지침서 (C++)

본 리뷰는 삼성 SW 역량테스트 기준으로 수행한다.

## 1. 시간 / 공간 복잡도 분석
- README.md 문제 설명에서 N 범위를 파악하라.
- N 최대일 때 1초 내 실행 가능한지 분석하라.
- O(N^3) 이상이면 경고하라.
- 불필요하게 큰 배열이나 낭비되는 다차원 배열 지적.

## 2. 구현 최적화
- std::sort / std::unique / memset 등으로 줄일 수 있는 코드 제안
- STL 남용 시 정적 배열 기반 구현 제안
- 상하좌우 탐색은 dx, dy 배열 사용 여부 확인

## 3. 엣지 케이스
- N=1
- 좌표 0 / N-1
- 초기화 누락
- 테스트케이스 반복 시 전역 변수 문제

## 4. 리팩토링 조언
- 더 단순한 알고리즘 가능 여부
- 가독성 문제
- 디버깅 위험 코드

반드시 **한국어 Markdown**으로 작성.

출력 구조:

## 시간 / 공간 복잡도
## 구현 최적화
## 엣지 케이스
## 리팩토링 조언
## 한 줄 평
"""


PROMPT_PY = """
# 네이버 코딩테스트 코드 리뷰 지침서 (Python)

네이버 코딩테스트 기준으로 코드를 리뷰한다.

## 1. 시간복잡도 및 입력 크기 분석
- README.md에서 N 범위를 파악
- Python 기준 1초 처리 가능 여부 분석
- O(N^2) 이상이면 경고 (특히 N ≥ 10^5)
- 불필요한 반복문 / 중첩 루프 지적

## 2. Pythonic 구현
다음 개선 여부 검토

- list comprehension
- enumerate
- zip
- collections (deque / Counter / defaultdict)
- heapq
- itertools

불필요한 반복문이나 장황한 구현은 Pythonic하게 단순화 제안.

## 3. 자료구조 선택
다음 문제 지적

- list 대신 set/dict가 유리한 경우
- queue 구현 시 deque 대신 list 사용
- heap 대신 sort 반복 사용

## 4. 엣지 케이스
- 빈 입력
- 길이 1 입력
- 음수 / 큰 값
- index error 가능성

## 5. 네이버 스타일 가독성
- 변수명 의미 부족
- 불필요한 중첩
- 함수 분리 가능성

반드시 **한국어 Markdown**으로 작성.

출력 구조:

## 시간 복잡도
## Pythonic 개선
## 자료구조 선택
## 엣지 케이스
## 리팩토링 조언
## 한 줄 평
"""


def read_readme(folder):

    path = os.path.join(folder, "README.md")

    if not os.path.exists(path):
        return ""

    with open(path) as f:
        return f.read()


def choose_prompt(file):

    ext = os.path.splitext(file)[1]

    if ext in [".cpp", ".cc", ".cxx"]:
        return PROMPT_CPP

    if ext in [".py"]:
        return PROMPT_PY

    return PROMPT_CPP


def review(code, readme, file):

    prompt = choose_prompt(file)

    full_prompt = (
        prompt +
        "\n\n[문제 설명]\n" +
        readme +
        "\n\n[풀이 코드]\n" +
        code
    )

    r = client.chat.completions.create(
        model="gpt-4o-mini",
        messages=[
            {"role": "system", "content": "코딩테스트 코드 리뷰어다."},
            {"role": "user", "content": full_prompt}
        ]
    )

    return r.choices[0].message.content


files = sys.argv[1].split()

for f in files:

    with open(f) as fp:
        code = fp.read()

    folder = os.path.dirname(f)

    readme = read_readme(folder)

    result = review(code, readme, f)

    out = os.path.join(folder, "REVIEW.md")

    with open(out, "w") as w:
        w.write("# AI 코드 리뷰\n\n")
        w.write(result)
