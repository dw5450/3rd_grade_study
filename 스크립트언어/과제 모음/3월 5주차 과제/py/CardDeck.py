class Card:
    def __init__(self, pattern, number):
        self.pattern = pattern
        self.number = number


    def __str__(self):
        return self.pattern + " " + self.number


class Deck:
    patternList = ["클럽", " 스페이드", "하트", "다이아몬드"]
    numberList = ["에이스", "2", "3", "4", "5", "6", "7", "8", "9", "10", "잭", "퀸", "킹"]
    def __init__(self):
        self.Cards = []
        self.cards = []
        for p in self.patternList:
            for n in self.numberList:
                self.Cards.append(Card(p, n))

    def __str__(self):
        strList = [str(c) for c in self.Cards]
        return str(strList)


    def __str__(self):
        return "{0}".format(self.cards)


    # 이걸 잘라서 저장하려면 어떻게 해야할가?


d = Deck()
print(d)