'''
    G:forward
    V:stop
    F~A:turn left(A means the maximun speed which is 400)
    H~L:turn right(L means the maximun speed which is 400)
    2021/7/19 btx
'''
import time
import tkinter
import serial
import tkinter.messagebox
#####函数部分######
def clear():# 清除文本框内容
    t.delete(1.0, 'end') 

def serialread():# 串口接收数据
    
    over_time = 30
    start_time = time.time()
    while True:
      end_time = time.time()
      if end_time - start_time < over_time:
       data = ser.read(ser.inWaiting())
       data = str(data)
      if data != '':
       t.insert('end',data)  # 将结果添加到文本框显示
       t.insert('end',data)

def serialwrite():#串口发送数据
    n = e.get()      
    ser.write(n.encode())
    clear()
    
def stop():
    ser.write(b"V")
    
def forward():
    ser.write(b"G")

def TurnRight():
    ser.write(b"A")

def TurnLeft():
    ser.write(b"L")
#####图形化界面####
window = tkinter.Tk()
window.title('串口调试程序1.0-btx')
window.geometry('300x450')
#标题1
l1 = tkinter.Label(window, text='串口发送')
l1.pack()
# 定义输入框
e = tkinter.Entry(window, width=15)
e.pack()
#发送数据按键
b1 = tkinter.Button(window, text="发送", command=serialwrite)
b1.pack()

#前进按键
b3 = tkinter.Button(window, text="前进", command=forward,bg='green')
b3.place(x = 120, y = 80 ,width=80, height=50)
#右转按键
b4 = tkinter.Button(window, text="右转", command=TurnRight,bg='yellow')
b4.place(x = 200, y = 80 ,width=80, height=50)
#左转按键
b2 = tkinter.Button(window, text="左转", command=TurnLeft,bg='yellow')
b2.place(x = 40, y = 80 ,width=80, height=50)
#停止按键
b5 = tkinter.Button(window, text="停止", command=stop,bg='red')
b5.place(x = 20, y = 150 ,width=260, height=50)
#标题2
#标题2
l1 = tkinter.Label(window, text='串口接收')
l1.place(x = 130, y = 210 ,width=80, height=30)
# 定义文本框
t = tkinter.Text(window, 
                 state='normal',  # 有disabled、normal 两个状态值，默认为normal
                 width=25, height=5
                 )
t.place(x = 20, y = 250 ,width=180, height=130)
#退出程序按键
b7 = tkinter.Button(window, text='退出', command=window.quit)
b7.place(x = 200, y = 290 ,width=80, height=30)

#####串口初始化#####
ser = serial.Serial('/dev/ttyUSB0', 9600)#ser = serial.Serial('/dev/ttyUSB0', 9600)//使用树莓派GPIO8端口作为串口时用AMA0,控制主控仓时，用USB0
if ser.isOpen == False:#串口启动判断
    ser.open()#串口启动 
ser.write(b"T")#串口发送数据






