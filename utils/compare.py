import subprocess

cases_gen = ['python', 'test.py']
solution1 = ['./B']
solution2 = ['./ans']

i = 0
while True:
    i += 1
    with open('in.txt', 'w') as f:
        subprocess.call(cases_gen, stdout=f)
    with open('in.txt') as f:
        a = subprocess.check_output(solution1, stdin=f)
    with open('in.txt') as f:
        b = subprocess.check_output(solution2, stdin=f)

    print('.', end='', flush=True)
    if a != b:
        print('\n!!!!!!!!!!!!!!!!!')
        break

