def Anagram(str1, str2):
    Flag = True
    if len(str1) == len(str2):
        list1 = list2 = []
        list1 += str1
        list2 += str2
        list1.sort()
        list2.sort()
        cnt = 0
        for i in range(len(str2)):
            if list1[i] != list2[i]:
                Flag = False
                break

    else :
        Flag = False

    if Flag == True:
        print("{0} & {1} are anagrams.".format(str1, str2))
    else :
        print("{0} & {1} are Not anagrams.".format(str1, str2))

n = eval(input())
for i in range(n):
    sl = input().split()

    str1 = sl[0]
    str2 = sl[1]
    Anagram(str1, str2)

  #  sl.clear()A