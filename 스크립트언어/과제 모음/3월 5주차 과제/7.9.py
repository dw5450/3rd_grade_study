class LinearEquation:
    def __init__(self, a, b, c, d, e, f):
        self.__a = a
        self.__b = b
        self.__c = c
        self. __d = d
        self.__e = e
        self.__f = f

    def get_a(self):
        return self.__a

    def get_b(self):
        return self.__b

    def get_c(self):
        return self.__c

    def get_d(self):
        return self.__d

    def get_e(self):
        return self.__e

    def get_f(self):
        return self.__f

    def isSolvable(self):
        if((self.__a * self.__d) - (self.__b * self.__c)) != 0:
            return True
        else : return False

    def getX(self):
        if(self.isSolvable()):
            return ((self.__e * self.__d) -  (self.__b * self.__f)) /((self.__a * self.__d) -  (self.__b * self.__c))
        else:
            print("이 방정식은 해가 없습니다.")
    def getY(self):
        if (self.isSolvable()):
            return ((self.__a * self.__f) -  (self.__e * self.__c)) /((self.__a * self.__d) -  (self.__b * self.__c))
        else:
            print("이 방정식은 해가 없습니다.")


def Line_equation(x1, y1, x2, y2):
    inclination = (y1 - y2) / (x1 - x2)
    c = y1 - (inclination * x1)
    return -inclination, 1, c

[x1, y1, x2, y2] = eval(input("첫 번째 선분의 양 끝점을 입력하세요 : "))

line1 = Line_equation(x1, y1, x2, y2)

[x3, y3, x4, y4] = eval(input("두 번째 선분의 양 끝점을 입력하세요 : "))

line2 = Line_equation(x3, y3, x4, y4)

LE = LinearEquation(line1[0], line1[1], line2[0], line2[1], line1[2], line2[2])

print ("교점 : (", LE.getX(), ", ", LE.getY(), ")")



