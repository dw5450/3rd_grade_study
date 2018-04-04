class BankAccount:
    def __init__(self, balance, name, number):
        self.name = name
        self.number =  number
        self.balance = balance

    def getBalance(self):
        return self.balance

    def getName(self):
        return self.name

    def getNuber(self):
        return self.number

    def withdraw(self, money):
        if(self.balance >= money ):
            self.balance -= money
            return money
        else : print ("잔액이 부족합니다.")

    def deposit(self, money):
           self.balance += money

    def showInfo(self):
        print("이   름 : ", self.name)
        print("계좌번호 : ", self.number)
        print("잔   액 : ", self.balance)



class SavingsAccount(BankAccount):
    def __init__(self, balance, name, number, interest_rate):
        BankAccount(self, balance, name, number )
        self.interest_rate = interest_rate

    def add_interest(self):
        self.balance += self.balance * self.interest_rate


class SavingsAccount(BankAccount):
    def __init__(self, balance, name, number, withdraw_charge):
        BankAccount(self, balance, name, number)
        self.withdraw_charge = withdraw_charge

    def withdraw(self, money):
        if (self.balance >= (money + self.withdraw_charge)):
            self.balance -= (money + self.withdraw_charge)
            return money
        else:
            print("잔액이 부족합니다.")



#예제를 어케 넣어야 할지 여쭈어 보자