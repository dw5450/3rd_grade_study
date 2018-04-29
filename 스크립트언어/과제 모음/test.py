class car:
    __num = 0
    def __init__(self):
        car.__num += 1

    def printNum():
        print("지금까지 생성된 차 대수 : ", car.__num)


a,b,c = car(), car(), car()

car.printNum()