#10진수를 2진수로 10진수를 2진수 문자열로 반환하는 재귀함수를 작성하시오

def decimalToHex(value):
    if value == 0:
        return ""
    else:
        r = value %16
        if ( r >= 10):
            temp = str(chr(ord('A') + r - 10))
        else : temp = str(r)
        return decimalToHex(value // 16) + temp

value = eval(input("10진수 입력:"))
print(value, "를 16진수로 바꾸면 ", decimalToHex(value))

