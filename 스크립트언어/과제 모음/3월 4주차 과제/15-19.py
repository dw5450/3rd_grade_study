#10진수를 2진수로 10진수를 2진수 문자열로 반환하는 재귀함수를 작성하시오

def decimalToBinary(value):
    if value == 0:
        return ""
    else:
        r = value %2
        return decimalToBinary(value // 2) + str(r)

value = eval(input("10진수 입력:"))
print(value, "를 이진수로 바꾸면 ", decimalToBinary(value))

