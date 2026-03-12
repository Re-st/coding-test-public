import os
import sys
from openai import OpenAI

client = OpenAI(api_key=os.environ["OPENAI_API_KEY"])

PROMPT = """
Review this competitive programming solution.

Return markdown only.

Include:
- Time complexity
- Space complexity
- Shorter implementation idea
- Edge cases to be careful about
- One-line takeaway
"""

def review(code):
    r = client.chat.completions.create(
        model="gpt-4o-mini",
        messages=[
            {"role": "system", "content": "You review competitive programming code."},
            {"role": "user", "content": PROMPT + "\n\n" + code}
        ]
    )
    return r.choices[0].message.content


files = sys.argv[1].split()

for f in files:

    with open(f) as fp:
        code = fp.read()

    result = review(code)

    folder = os.path.dirname(f)
    out = os.path.join(folder, "REVIEW.md")

    with open(out, "w") as w:
        w.write("# AI Review\n\n")
        w.write(result)
