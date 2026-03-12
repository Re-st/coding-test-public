import os
import sys
from openai import OpenAI

client = OpenAI(api_key=os.environ["OPENAI_API_KEY"])


PROMPT_CPP = """
# 삼성 SW 역량테스트 합격 지침서 (C++)

본 리뷰는 삼성 SW 역량테스트 기준으로 수행한다.

## 1. 시간 / 공간 복잡도 분석
- README.md에서 N 범위를 파악
- N 최대일 때 1초 내 실행 가능 여부
- O(N^3) 이상이면 경고
- 불필요한 대형 배열 지적

## 2. 구현 최적화
- std::sort / memset 등으로 줄일 수 있는 코드 제안
- STL 남용 시 정적 배열 기반 구현 제안
- dx dy 배열 기반 탐색 여부 확인

## 3. 엣지 케이스
- N=1
- 좌표 경계 (0 / N-1)
- 초기화 누락
- 테스트케이스 반복 문제

## 4. 리팩토링
- 더 단순한 알고리즘 제안
- 가독성 문제
- 디버깅 위험 코드

한국어 Markdown으로 작성

## 시간 / 공간 복잡도
## 구현 최적화
## 엣지 케이스
## 리팩토링 조언
## 한 줄 평
"""


PROMPT_PY = """
# 네이버 코딩테스트 코드 리뷰 지침 (Python)

네이버 코딩테스트 기준으로 리뷰한다.

## 1. 시간복잡도
- README에서 N 범위 파악
- Python 기준 시간 초과 위험 분석
- 불필요한 중첩 루프 지적

## 2. Pythonic 구현
다음 활용 여부 검토

- list comprehension
- enumerate
- zip
- collections
- heapq

## 3. 자료구조 선택
- list vs set/dict
- deque 대신 list 사용 여부
- heap 대신 반복 sort 여부

## 4. 엣지 케이스
- 빈 입력
- 길이 1
- index error 가능성

## 5. 가독성
- 변수명
- 불필요한 중첩
- 함수 분리 가능성

한국어 Markdown으로 작성

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

    if ext == ".py":
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
            {"role": "system", "content": "코딩테스트 코드 리뷰어"},
            {"role": "user", "content": full_prompt}
        ]
    )

    return r.choices[0].message.content


def find_unreviewed_files():

    targets = []

    for root, _, files in os.walk("."):

        for f in files:

            if not f.endswith((".cpp", ".cc", ".cxx", ".py")):
                continue

            src = os.path.join(root, f)
            review_path = os.path.join(root, "REVIEW.md")

            if not os.path.exists(review_path):
                targets.append(src)

    return targets


# push된 파일
push_files = []
if len(sys.argv) > 1:
    push_files = sys.argv[1].split()

# 기존 리뷰 안된 파일
unreviewed = find_unreviewed_files()

targets = list(set(push_files + unreviewed))

for f in targets:

    with open(f) as fp:
        code = fp.read()

    folder = os.path.dirname(f)

    readme = read_readme(folder)

    result = review(code, readme, f)

    out = os.path.join(folder, "REVIEW.md")

    with open(out, "w") as w:
        w.write("# AI 코드 리뷰\n\n")
        w.write(result)
