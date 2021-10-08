#!/usr/bin/env python3
import sys
import random

the_board = None
the_turn = None

def board_winner(board):
    for i in range(3):
        if board[i] == board[i+3] == board[i+6] != 0:
            return board[i]
        if board[3*i] == board[3*i+1] == board[3*i+2] != 0:
            return board[3*i]
    if board[0] == board[4] == board[8] != 0:
        return board[0]
    if board[2] == board[4] == board[6] != 0:
        return board[2]
    return 0

def board_full(board):
    return all(x != 0 for x in board)

state_winners = {}
def state_winner(board, turn):
    key = (tuple(board), turn)
    if key in state_winners:
        return state_winners[key]
    win = board_winner(board)
    if win != 0 or board_full(board):
        return (win, -1)
    win = -turn
    opt_move = -1
    perm = list(range(9))
    random.shuffle(perm)
    for i in perm:
        if board[i] != 0:
            continue
        board[i] = turn
        w = state_winner(board, -turn)[0]
        board[i] = 0
        if w == 0:
            win = 0
            opt_move = i
        if w == turn:
            win = turn
            opt_move = i
            break
    ret = (win, opt_move)
    state_winners[key] = ret
    return ret

def random_runner():
    perm = list(range(9))
    random.shuffle(perm)
    for i in perm:
        if not the_board[i]:
            yield i
    assert False

def opt_runner():
    while True:
        w = state_winner(the_board, the_turn)
        assert w[0] != -the_turn
        yield w[1]

def safe_print(n):
    try:
        print(n)
        sys.stdout.flush()
    except IOError:
        pass

def print_board(board):
    lut = 'o.x'
    for i in range(3):
        li = ''
        for c in board[3*i:3*(i+1)]:
            li += lut[c+1]
        safe_print(li)

def pl_move(board):
    s2 = ''
    for i in range(3):
        s = input().strip()
        if len(s) != 3:
            sys.exit(43)
        s2 += s
    assert len(s2) == 9
    mismatches = 0
    b2 = []
    for i in range(9):
        c = s2[i]
        if c == 'o':
            d = -1
        elif c == '.':
            d = 0
        elif c == 'x':
            d = 1
        else:
            sys.exit(43)
        if d != board[i]:
            if board[i] != 0:
                sys.exit(43)
            mismatches += 1
        b2.append(d)
    if mismatches != 1:
        sys.exit(43)
    return b2

def main():
    [case, starting, strategy, seed] = map(int, open(sys.argv[1], 'r').read().strip().split())
    random.seed(seed*100 + strategy*8 + starting*4 + case)

    starting = (starting == 1)
    board = [0] * 9
    require_win_if_possible = (case == 2 or case == 3)
    require_nonlose = (case == 1 or case == 3)

    g = [None]
    if strategy == 0:
        g[0] = random_runner()
    elif strategy == 1:
        g[0] = opt_runner()
    else:
        assert False

    def ai_move(board):
        global the_turn, the_board
        the_board = board
        the_turn = -1
        v = next(g[0])
        assert 0 <= v < 9
        assert board[v] == 0
        board[v] = -1
        print_board(board)
        return board

    try:
        if starting:
            safe_print("first")
            safe_print('...')
            safe_print('...')
            safe_print('...')
            turn = 1
        else:
            safe_print("second")
            turn = -1
            ai_move(board)
            turn = 1

        had_win = False
        while board_winner(board) == 0 and not board_full(board):
            if turn == -1:
                board = ai_move(board)
                turn = 1
            else:
                if state_winner(board, 1)[0] == 1:
                    had_win = True
                board = pl_move(board)
                turn = -1

        # (Per spec the program should terminate here, but it's unclear how to check that. So don't.)

        w = board_winner(board)
        if require_win_if_possible and had_win and w != 1:
            sys.exit(43)
        if require_nonlose and w == -1:
            sys.exit(43)
        sys.exit(42)
    except (EOFError, UnicodeError):
        sys.exit(43)

main()
