GROUP_SCORES = [10, 15, 25, 25, 40]
GROUP_CASES = [[0, 1, 2, 3, 4, 5, 6, 7, 8, 9], [20, 21, 22, 23, 24, 25, 26, 27, 28, 29], [40, 41, 42, 43, 44, 45, 46, 47, 48, 49], [10, 11, 12, 13, 14, 15, 16, 17, 18, 19], [30, 31, 32, 33, 34, 35, 36, 37, 38, 39]]
import sys

def is_int(arg):
    try:
        int(arg)
        return True
    except:
        return False


def main():
    if "ignore" in sys.argv:
        print("AC 0")
    elif "groups" in sys.argv:
        scores = []
        for line in sys.stdin.readlines():
            verdict, score = line.split()
            if verdict != "AC":
                scores.append(0)
            else:
                scores.append(score)
        score = 0
        for group in range(len(GROUP_SCORES)):
            group_score = GROUP_SCORES[group]
            for case in GROUP_CASES[group]:
                if scores[case] == 0:
                    group_score = 0
            score += group_score
        print("AC %s" % score)
    else:
        for line in sys.stdin.readlines():
            print(line)

main()

