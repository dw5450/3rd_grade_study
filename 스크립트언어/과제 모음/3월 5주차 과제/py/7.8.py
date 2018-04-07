import time

class StopWatch:
    def __init__(self):
        self.__startTime = time.time()

    def start(self):
        self.__startTime = time.time()

    def stop(self):
        self.__endTime = time.time()

    def getStartTime(self):
        return self.__startTime

    def getStopTime(self):
        return self.__endTime

    def getElapsedTime(self):
        return int ((self.__endTime - self.__startTime) * 1000)

s = StopWatch()

sum = 0

for i in range(1, 1000001):
    sum += i

s.stop()
print("경과시간:", s.getElapsedTime())