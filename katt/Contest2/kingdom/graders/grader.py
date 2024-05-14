#!/usr/bin/env python3

import sys


def worst_error(verdicts):
    sorting_order = ['JE', 'IF', 'RTE', 'MLE', 'TLE', 'OLE', 'WA', 'PE', 'AC']
    verdicts += ['AC']
    index = min(sorting_order.index(verdict) for verdict in verdicts)
    return sorting_order[index]

def first_error(verdicts):
    for verdict in verdicts:
        if verdict != 'AC':
            return verdict
    return 'AC'

def always_accept(verdicts):
    return 'AC'

verdict_aggregators = {
    'worst_error': worst_error,
    'no_errors': worst_error,
    'first_error': first_error,
    'always_accept': always_accept
}


def avg(scores):
    return 1.0*sum(scores) / len(scores)

score_aggregators = {
    'sum': sum,
    'avg': avg,
    'max': max,
    'min': min
}


aggregate_scores = score_aggregators['sum']
aggregate_verdicts = verdict_aggregators['worst_error']
ignore_sample = False
accept_if_any_accepted = False

subtask_score=1
for flag in sys.argv:
    if flag in score_aggregators:
        aggregate_scores = score_aggregators[flag]
    if flag in verdict_aggregators:
        aggregate_verdicts = verdict_aggregators[flag]
    if flag == 'ignore_sample':
        ignore_sample = True
    if flag == 'accept_if_any_accepted':
        accept_if_any_accepted = True
    if "subtask_score" in flag:
        subtask_score = int(flag.split("=")[1])

try:
    data = sys.stdin.read().split()
    verdicts = data[0::2]
    scores = list(map(float, data[1::2]))
    assert len(verdicts) == len(scores)
    if ignore_sample:
        assert 1 <= len(verdicts) <= 2
        verdicts = verdicts[-1:]
        scores = scores[-1:]
    if accept_if_any_accepted and 'AC' in verdicts:
        verdict = 'AC'
    else:
        verdict = aggregate_verdicts(verdicts)
    score = aggregate_scores(scores)*subtask_score
    print('%s %f' % (verdict, score))
except:
    print('JE')