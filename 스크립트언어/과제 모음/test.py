import http.client
import json
import urllib


server = "api.neople.co.kr"
#myApiKey = "9BdgXATgR7uy3XIzIaJPBHfECPoJGKlq"
conn = http.client.HTTPSConnection(server)
'''


CharaterName = urllib.parse.quote("비구름마녀")

conn.request("GET", "https://api.neople.co.kr/df/servers/cain/characters?characterName=" +CharaterName + "&limit=<limit>&wordType=<wordType>&apikey=" +myApiKey) #서버에 GET 요청
req = conn.getresponse() 			#openAPI 서버에서 보내온 요청을 받아옴
print(req.status, req.reason)
cLen = req.getheader("Content-Length") 	#가져온 데이터 길이
data = req.read(int(cLen))
dict = json.loads(data)

print (dict['rows'][0]['characterName'])
'''
#print(dict['rows']['characterName'])



def getItemInfo(itmemName):
    urlItemName = urllib.parse.quote(itmemName)
    global conn
    conn.request("GET","https://api.neople.co.kr/df/items?itemName="+urlItemName+"&q=minLevel:<minLevel>,maxLevel:<maxLevel>,rarity:<rarity>,trade:<trade>&limit=<limit>&wordType=<wordType>&apikey=9BdgXATgR7uy3XIzIaJPBHfECPoJGKlq")  # 서버에 GET 요청
    req = conn.getresponse()  # openAPI 서버에서 보내온 요청을 받아옴

    if(req.status == 200):
        cLen = req.getheader("Content-Length")  # 가져온 데이터 길이
        data = req.read(int(cLen))
        dict = json.loads(data)
        ItemId = dict["rows"][0]['itemId']

        conn.request("GET","https://api.neople.co.kr/df/items/"+ItemId+"?apikey=9BdgXATgR7uy3XIzIaJPBHfECPoJGKlq")  # 서버에 GET 요청
        req = conn.getresponse()
        cLen = req.getheader("Content-Length")  # 가져온 데이터 길이
        data = req.read(int(cLen))
        dict = json.loads(data)
        print(dict['itemExplain'])

getItemInfo("창성의 구원자 - 빗자루")