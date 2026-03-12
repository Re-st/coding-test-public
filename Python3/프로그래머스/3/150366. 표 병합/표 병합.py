def solution(commands):
    # 첫번째 range(51) 도 * 51하니까 안되네..
    sheet = [["" for _ in range(51)] for _ in range(51)]
    answer = []
    merge = dict() # 좌표: 대표좌표
    for cmd in commands:
        kw = cmd[:2]
        if kw == "UP":
            cmds = cmd.split()
            if len(cmds) == 4:
                _, r, c, value = cmds
                r = int(r)
                c = int(c)
                if (r, c) in merge.keys():
                    (r, c) = merge[(r, c)]
                sheet[r][c] = value
            else:
                _, value1, value2 = cmds
                for i in range(1, 51):
                    for j in range(1, 51):
                        if sheet[i][j] == value1:
                            sheet[i][j] = value2
        elif kw == "ME":
            _, r1, c1, r2, c2 = cmd.split()
            [r1, c1, r2, c2] = map(int, [r1, c1, r2, c2])
            if (r1, c1) == (r2, c2):
                continue
            if (r1, c1) in merge.keys() and (r2, c2) in merge.keys() and merge[(r1, c1)] == merge[(r2, c2)]:
                continue
            if (r1, c1) in merge.keys():
                (r1, c1) = merge[(r1, c1)]
            else:
                merge[(r1, c1)] = (r1, c1)
            if (r2, c2) in merge.keys():
                (r2, c2) = merge[(r2, c2)]
                for (k, v) in merge.items():
                    if (r2, c2) == v:
                        merge[k] = (r1, c1)
            else:
                merge[(r2, c2)] = (r1, c1)
            if sheet[r1][c1] != "":
                sheet[r2][c2] = ""
            elif sheet[r2][c2] != "":
                sheet[r1][c1] = sheet[r2][c2]
                sheet[r2][c2] = ""
        elif kw == "UN":
            _, r, c = cmd.split()
            r = int(r)
            c = int(c)
            if (r, c) in merge.keys():
                (rhead, chead) = merge[(r, c)]
                if (rhead, chead) != (r, c):
                    sheet[r][c] = sheet[rhead][chead]
                    sheet[rhead][chead] = ""
                for (k, v) in merge.copy().items():
                    # if (rhead, chead) == v: 왜 이런식의 비교가 안되지? 아하. merge가 아니라 merge.items()여야 하는구나.
                    if (rhead, chead) == v:
                        merge.pop(k)
        else:
            _, r, c = cmd.split()
            r = int(r)
            c = int(c)
            if (r, c) in merge.keys():
                (r, c) = merge[(r, c)]
            kw = sheet[r][c]
            answer.append("EMPTY" if kw == "" else kw)
        # if cmd == "UPDATE korean hansik":
        #     for i in range(1, 5):
        #         for j in range(1, 5):
        #             print(sheet[i][j])
    # for i in range(1, 5):
    #     for j in range(1, 5):
    #         print(sheet[i][j])
    return answer