
class BankAccount:
    def __init__(self, balance, name, number):

    def __str__(self):
        return "잔액" + str(self.balance)

class SavingsAccount(BankAccount):
    def __init__(self, balance, name, number, interest_rate):
        super().__init__(balance, name, number)



