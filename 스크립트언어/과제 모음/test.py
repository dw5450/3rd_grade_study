
from tkinter import *
from io import BytesIO
import urllib
import urllib.request
from io import BytesIO
from PIL import Image, ImageTk
from 던파API파싱하기 import *

root = Tk()
root.geometry("500x500+500+200")

# openapi로 이미지 url을 가져옴.
비구름마녀 = urllib.parse.quote('비구름마녀')

'https://img-api.neople.co.kr/df/servers/<serverId>/characters/<characterId>?zoom=<zoom>'
url = 'https://img-api.neople.co.kr/df/servers/cain/characters/'+ '583341709cfa6d9768d1f6b13c17276f' + '?zoom=<zoom>'
with urllib.request.urlopen(url) as u:
    raw_data = u.read()

im = Image.open(BytesIO(raw_data))
image = 캐릭터이미지가져오기('카인', '비구름마녀')

label = Label(root, image=image, height=400, width=400)
label.pack()
label.place(x=0, y=0)
root.mainloop()
