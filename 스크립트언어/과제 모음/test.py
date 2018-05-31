from tkinter import *
from tkinter import font
import tkinter.messagebox

g_Tk = Tk()
g_Tk.geometry("400x600+750+200")
DataList = []

## GUI의 제목을 탑에다 적자
def InitTopText():
    TempFont = font.Font(g_Tk, size=20, weight='bold', family = 'Consolas')
    MainText = Label(g_Tk, font = TempFont, text="[던파스카우터!]")
    MainText.pack()
    MainText.place(x=100, y = 30)

def InitSearchListBox():
    global SearchListBox
    TempFont = font.Font(g_Tk, size=15, weight='bold', family='Consolas')
    MainText = Label(g_Tk, font = TempFont, text="서버 ")
    MainText.pack()
    MainText.place(x=10, y = 100)

    ListBoxScrollbar = Scrollbar(g_Tk)
    ListBoxScrollbar.pack()
    ListBoxScrollbar.place(x=210, y=90)

    SearchListBox = Listbox(g_Tk, font=TempFont, activestyle='none',
                            width=10, height=1, borderwidth=12, relief='ridge',
                            yscrollcommand=ListBoxScrollbar.set)

    SearchListBox.insert(1, "카인")
    SearchListBox.insert(2, "디레지에")
    SearchListBox.insert(3, "시로코")
    SearchListBox.insert(4, "프레이")
    SearchListBox.insert(5, "카시야스")
    SearchListBox.insert(6, "힐더")
    SearchListBox.insert(7, "안톤")
    SearchListBox.insert(8, "바칼")
    SearchListBox.pack()
    SearchListBox.place(x=70, y=90)
    ListBoxScrollbar.config(command=SearchListBox.yview)

def InitInputLabel():
    global InputLabel
    TempFont = font.Font(g_Tk, size=15, weight='bold', family = 'Consolas')
    MainText = Label(g_Tk, font=TempFont, text="이름 ")
    MainText.pack()
    MainText.place(x=10, y=155)

    InputLabel = Entry(g_Tk, font = TempFont, width = 15, borderwidth = 12, relief = 'ridge')
    InputLabel.pack()
    InputLabel.place(x=70, y=145)

def InitSearchButton():
    TempFont = font.Font(g_Tk, size=12, weight='bold', family='Consolas')
    SearchButton = Button(g_Tk, font=TempFont, text="검색", command = SearchButtonAction)
    SearchButton.pack()
    SearchButton.place(x=330, y=100)

def SearchButtonAction():
    global SearchListBox
    global InputLabel
    RenderText.configure(state='normal')
    RenderText.delete(0.0, END)
    iSearchIndex = SearchListBox.yview()[0]
    print(InputLabel.get())
    #print(int(iSearchIndex//0.125))


def InitRenderText():
    global RenderText

    RenderTextScrollbar = Scrollbar(g_Tk)
    RenderTextScrollbar.pack()
    RenderTextScrollbar.place(x=375, y=220)

    TempFont = font.Font(g_Tk, size=10, family='Consolas')
    RenderText = Text(g_Tk, width=49, height=23, borderwidth=12,
                      relief='ridge', yscrollcommand=RenderTextScrollbar.set)
    RenderText.pack()
    RenderText.place(x=10, y=235)
    RenderTextScrollbar.config(command=RenderText.yview)
    RenderTextScrollbar.pack(side=RIGHT, fill=BOTH)

    RenderText.configure(state='disabled')

InitTopText()
InitSearchListBox()
InitInputLabel()
InitSearchButton()
InitRenderText()
g_Tk.mainloop()