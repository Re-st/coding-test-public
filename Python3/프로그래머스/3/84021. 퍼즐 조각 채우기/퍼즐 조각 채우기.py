# board -> {hash1, h2, h3, h4} list
def read(board):
    n = len(board)
    visited = [[False] * n for _ in range(n)]
    ret = []
    for i in range(n):
        for j in range(n):
            if not visited[i][j] and board[i][j]:
                visited[i][j] = True
                neighbor = set({(i, j)})
                piece = set({(i, j)})
                while neighbor:
                    ii, jj = neighbor.pop()
                    for di, dj in [(0, -1), (0, 1), (1, 0), (-1, 0)]:
                        newi = ii + di
                        newj = jj + dj
                        if 0 <= newi < n and 0 <= newj < n and not visited[newi][newj] and board[newi][newj]:
                            visited[newi][newj] = True
                            neighbor.add((newi, newj))
                            piece.add((newi, newj))
                pieceList = list((i - min(i for (i, _) in piece), j - min(j for (_, j) in piece)) for (i, j) in piece)
                pieceInNum = -1
                for _ in range(4):
                    # rotate piece (i, j)->(j, 5 - i)
                    pieceList = [(5 - j, i) for (i, j) in pieceList]
                    pieceList = list((i - min(i for (i, _) in pieceList), j - min(j for (_, j) in pieceList)) for (i, j) in pieceList)
                    # make a number
                    num = sum(1 << (6 * i + j) for (i, j) in pieceList)
                    pieceInNum = max(pieceInNum, num)
                ret.append(pieceInNum)
    return ret

def countll(hole):
    ans = 0
    while hole:
        if hole % 2:
            ans += 1
        hole //= 2
    return ans

def solution(game_board, table):
    game_board = [[1 - i for i in row] for row in game_board]
    game_board = read(game_board)
    table = read(table)
    answer = 0
    print(game_board)
    for hole in game_board:
        if hole in table:
            table.remove(hole) # once?
            answer += countll(hole)
    return answer