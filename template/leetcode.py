#!/usr/bin/python3
# pylint: disable=no-value-for-parameter
# {{{
import sys
from typing import List
import inspect

def read_tree(line):
    lst = eval(line.replace('null', 'None'))
    if not lst:
        return None
    root = TreeNode(lst[0])
    tmp = [root]
    for i in range(1, len(lst)):
        node = TreeNode(lst[i]) if lst[i] is not None else None

        j = (i + 1) // 2 - 1
        if i % 2 == 1:
            tmp[j].left = node
        else:
            tmp[j].right = node
        tmp.append(node)
    return root


def read(params, lines):
    data = []
    for param, line in zip(params.values(), lines):
        if param._annotation == type(TreeNode()):
            data.append(read_tree(line))
        else:
            data.append(eval(line))
    return data


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
# }}}



sol = Solution()
method = sol.

# {{{
params = inspect.signature(method).parameters
nparams = len(params)
lines = list(sys.stdin.readlines())
for i in range(0, len(lines), nparams):
    print(method(*read(params, lines[i:i + nparams])))
# }}}
