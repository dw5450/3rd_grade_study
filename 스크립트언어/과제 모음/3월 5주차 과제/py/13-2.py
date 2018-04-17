f =  open('test.txt', 'r')

str =  f.read()

print ("문자 {0}". format(len(str)))
print ("단어 {0}". format(len(str.split())))
print ("행 {0}". format(len(str.split('\n'))))