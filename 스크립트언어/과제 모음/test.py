from functools import *
	#functools 모듈에서 *가져옮
             #reduce 함수 사용하기 위해

def intersect(*ar):     #교집합
    return reduce(__intersectSC, ar)

def __intersectSC(listX, listY):
    setList = []
    for x in listX:
        if x in listY:
            setList.append(x)
    return setList


 def difference(*ar):    #차집합
    setList = []
    intersectSet = intersect(*ar)
    unionSet = union(*ar)
    for x in unionSet:
        if not x in intersectSet:
            setList.append(x)
    return setList

def union(*ar):            #합집합
    setList = []
    for item in ar:
        for x in item:
            if not x in setList:
                setList.append(x)
    return setList


