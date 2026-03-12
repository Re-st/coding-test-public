import sys

input = sys.stdin.readline

n = int(input())
schedules = []
for _ in range(n):
    a, b = map(int, input().split())
    schedules.append((a, b))

start = min(s[0] for s in schedules)
schedules.sort(key=lambda x:(x[1], x[0]))

count = 1
last_end_time = schedules[0][1]

for i in range(1, n):
    start_time, end_time = schedules[i]
    
    if start_time >= last_end_time:
        count += 1
        last_end_time = end_time

print(count)