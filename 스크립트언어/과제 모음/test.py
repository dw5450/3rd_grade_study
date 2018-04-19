
def f(num):
    result = 0
    for i in range(num):
        result += num * i + i

    return result


n = eval(input())

print(f(n))