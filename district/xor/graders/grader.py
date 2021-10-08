GROUP_SCORES = [6, 10, 12, 19, 24, 33, 41, 15]
GROUP_CASES = [[0, 18, 36, 54, 72], [11, 29, 47, 65, 83], [25, 26, 27, 43, 44, 45, 61, 62, 63, 7, 79, 8, 80, 81, 9], [2, 20, 21, 22, 3, 38, 39, 4, 40, 56, 57, 58, 74, 75, 76], [11, 13, 14, 15, 2, 20, 21, 22, 29, 3, 31, 32, 33, 38, 39, 4, 40, 47, 49, 50, 51, 56, 57, 58, 65, 67, 68, 69, 74, 75, 76, 83, 85, 86, 87], [1, 19, 2, 20, 21, 22, 23, 24, 3, 37, 38, 39, 4, 40, 41, 42, 5, 55, 56, 57, 58, 59, 6, 60, 73, 74, 75, 76, 77, 78], [1, 11, 12, 13, 14, 15, 16, 17, 19, 2, 2, 20, 20, 21, 21, 22, 22, 23, 24, 29, 3, 3, 30, 31, 32, 33, 34, 35, 37, 38, 38, 39, 39, 4, 4, 40, 40, 41, 42, 47, 48, 49, 5, 50, 51, 52, 53, 55, 56, 56, 57, 57, 58, 58, 59, 6, 60, 65, 66, 67, 68, 69, 70, 71, 73, 74, 74, 75, 75, 76, 76, 77, 78, 83, 84, 85, 86, 87, 88, 89], [10, 28, 46, 64, 82]]
import sys

def is_int(arg):
    try:
        int(arg)
        return True
    except:
        return False


def main():
    if "ignore" in sys.argv:
        print "AC 0"
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
        print "AC %s" % score
    else:
        for line in sys.stdin.readlines():
            print line

main()

