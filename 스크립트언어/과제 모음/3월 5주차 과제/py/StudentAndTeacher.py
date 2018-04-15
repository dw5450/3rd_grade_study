class Person :
    def __init__(self, name, number):
        self.name = name
        self.number = number

    def __str__(self):
        str = "이름={0} \n 주민번호={1}\n".format(self.name, self.number)

        return str

class Student(Person):
    def __init__(self, name, number, classes, gda):
        Person.__init__(self, name, number)
        self.classes = classes
        self.gda = gda

    def __str__(self):
        str = Person.__str__(self) + "수강과목={0}\n평점={1}".format(self.classes, self.gda)
        return str

class Teacher(Person):
    def __init__(self, name, number, courses, salary):
        Person.__init__(self, name, number)
        self.courses = courses
        self.salary = salary
    def __str__(self):
        str = Person.__str__(self) + "강의과목={0}\n월급={1}".format(self.courses, self.salary)
        return str


s = Student("홍길동", 12345678, ['자료구조'], 0)
print(s,'\n')
t = Teacher("김철수",123456780, ['Python'], 3000000)
print(t)