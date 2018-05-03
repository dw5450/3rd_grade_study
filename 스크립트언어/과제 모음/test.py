import http.client
import json


server = "api.neople.co.kr"

conn = http.client.HTTPSConnection(server)

conn.request("GET", "/df/servers?apikey=9BdgXATgR7uy3XIzIaJPBHfECPoJGKlq") #서버에 GET 요청
req = conn.getresponse() 			#openAPI 서버에서 보내온 요청을 받아옴
print(req.status, req.reason)
cLen = req.getheader("Content-Length") 	#가져온 데이터 길이
data = req.read(int(cLen))
dict = json.loads(data)

for d in dict['rows']:
    print (d)