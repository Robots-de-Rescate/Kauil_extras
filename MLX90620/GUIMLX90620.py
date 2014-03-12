from Tkinter import *
import random
import serial


class MyApp(Tk):
    def __init__(self):
        Tk.__init__(self)
        fr = Frame(self,width=480, height=800) # Se utiliza un frame donde se colocan 64 canvas
        fr.grid()

        self.do_blink = False # Bandera que de ser verdadera la aplicacion empieza a graficar la temperatura
        self.valor= [] # Arreglo que sirve para recivir los valores del sensor
        self.new_color=[] # Este arreglo guarda los valores recibidos del sensor pero convertidos a un valor hexadecimal dependiendo de la temperatura
        self.MaxTemp=50 # Este es el valor de temperatura que graficara como una temperatura caliente, entre mas alto sea el numero menor seran los cambios de color
        self.resolucion=1 # Variable de resoluciond de cambios de color
        self.rango_de_color=1 # Variable con fines de control
        self.h=50 # Este numero describe la altura de cada frame 
        self.w=30 # Este numero describe lo ancho de cada frame
        self.ser = serial.Serial('/dev/ttyACM0', 9600)
        self.start_button = Button(fr, text="start blinking", # Botones para empezar a leer la temperatura y graficarla asi como tambien para detener la aplicacion
                              command=self.start_blinking)
        self.stop_button = Button(fr, text="stop blinking",
                              command=self.stop_blinking)


        self.A1=Canvas(fr, bg="#191970", height=self.h, width=self.w)  # Se hacen 64 canvas representando cada uno de los pixeles de la grafica y del sensor
        self.A2=Canvas(fr, bg="#191970", height=self.h, width=self.w)  # Las letras indican el numero de fila de arriba a abajo y los numeros el numero de pixel en
        self.A3=Canvas(fr, bg="#191970", height=self.h, width=self.w)  # la fila
        self.A4=Canvas(fr, bg="#32CD32", height=self.h, width=self.w)
        self.A5=Canvas(fr, bg="#191970", height=self.h, width=self.w)
        self.A6=Canvas(fr, bg="#32CD32", height=self.h, width=self.w)
        self.A7=Canvas(fr, bg="#191970", height=self.h, width=self.w)
        self.A8=Canvas(fr, bg="#32CD32", height=self.h, width=self.w)
        self.A9=Canvas(fr, bg="#191970", height=self.h, width=self.w)
        self.A10=Canvas(fr, bg="#191970", height=self.h, width=self.w)
        self.A11=Canvas(fr, bg="#191970", height=self.h, width=self.w)
        self.A12=Canvas(fr, bg="#32CD32", height=self.h, width=self.w)
        self.A13=Canvas(fr, bg="#191970", height=self.h, width=self.w)
        self.A14=Canvas(fr, bg="#191970", height=self.h, width=self.w)
        self.A15=Canvas(fr, bg="#32CD32", height=self.h, width=self.w)
        self.A16=Canvas(fr, bg="#191970", height=self.h, width=self.w)

        self.B1=Canvas(fr, bg="#32CD32", height=self.h, width=self.w)
        self.B2=Canvas(fr, bg="#191970", height=self.h, width=self.w)
        self.B3=Canvas(fr, bg="#32CD32", height=self.h, width=self.w)
        self.B4=Canvas(fr, bg="#32CD32", height=self.h, width=self.w)
        self.B5=Canvas(fr, bg="#191970", height=self.h, width=self.w)
        self.B6=Canvas(fr, bg="#32CD32", height=self.h, width=self.w)
        self.B7=Canvas(fr, bg="#191970", height=self.h, width=self.w)
        self.B8=Canvas(fr, bg="#32CD32", height=self.h, width=self.w)
        self.B9=Canvas(fr, bg="#191970", height=self.h, width=self.w)
        self.B10=Canvas(fr, bg="#32CD32", height=self.h, width=self.w)
        self.B11=Canvas(fr, bg="#191970", height=self.h, width=self.w)
 	self.B12=Canvas(fr, bg="#32CD32", height=self.h, width=self.w)
        self.B13=Canvas(fr, bg="#191970", height=self.h, width=self.w)
        self.B14=Canvas(fr, bg="#191970", height=self.h, width=self.w)
        self.B15=Canvas(fr, bg="#32CD32", height=self.h, width=self.w)
        self.B16=Canvas(fr, bg="#191970", height=self.h, width=self.w)

        self.C1=Canvas(fr, bg="#32CD32", height=self.h, width=self.w)
        self.C2=Canvas(fr, bg="#191970", height=self.h, width=self.w)
        self.C3=Canvas(fr, bg="#32CD32", height=self.h, width=self.w)
        self.C4=Canvas(fr, bg="#32CD32", height=self.h, width=self.w)
        self.C5=Canvas(fr, bg="#191970", height=self.h, width=self.w)
        self.C6=Canvas(fr, bg="#32CD32", height=self.h, width=self.w)
        self.C7=Canvas(fr, bg="#191970", height=self.h, width=self.w)
        self.C8=Canvas(fr, bg="#32CD32", height=self.h, width=self.w)
        self.C9=Canvas(fr, bg="#191970", height=self.h, width=self.w)
        self.C10=Canvas(fr, bg="#191970", height=self.h, width=self.w)
        self.C11=Canvas(fr, bg="#191970", height=self.h, width=self.w)
        self.C12=Canvas(fr, bg="#32CD32", height=self.h, width=self.w)
        self.C13=Canvas(fr, bg="#191970", height=self.h, width=self.w)
        self.C14=Canvas(fr, bg="#32CD32", height=self.h, width=self.w)
        self.C15=Canvas(fr, bg="#191970", height=self.h, width=self.w)
        self.C16=Canvas(fr, bg="#191970", height=self.h, width=self.w)

        self.D1=Canvas(fr, bg="#191970", height=self.h, width=self.w)
        self.D2=Canvas(fr, bg="#191970", height=self.h, width=self.w)
        self.D3=Canvas(fr, bg="#32CD32", height=self.h, width=self.w)
        self.D4=Canvas(fr, bg="#32CD32", height=self.h, width=self.w)
        self.D5=Canvas(fr, bg="#191970", height=self.h, width=self.w)
        self.D6=Canvas(fr, bg="#191970", height=self.h, width=self.w)
        self.D7=Canvas(fr, bg="#191970", height=self.h, width=self.w)
        self.D8=Canvas(fr, bg="#32CD32", height=self.h, width=self.w)
        self.D9=Canvas(fr, bg="#191970", height=self.h, width=self.w)
        self.D10=Canvas(fr, bg="#32CD32", height=self.h, width=self.w)
        self.D11=Canvas(fr, bg="#191970", height=self.h, width=self.w)
        self.D12=Canvas(fr, bg="#32CD32", height=self.h, width=self.w)
        self.D13=Canvas(fr, bg="#191970", height=self.h, width=self.w)
        self.D14=Canvas(fr, bg="#32CD32", height=self.h, width=self.w)
        self.D15=Canvas(fr, bg="#191970", height=self.h, width=self.w)
        self.D16=Canvas(fr, bg="#191970", height=self.h, width=self.w)


        self.A1.grid(row=0,column=0)  # Aqui se define la posicion de cada canvas o pixel en el frame
        self.A2.grid(row=0,column=1)
        self.A3.grid(row=0,column=2)
        self.A4.grid(row=0,column=3)
        self.A5.grid(row=0,column=4)
        self.A6.grid(row=0,column=5)
        self.A7.grid(row=0,column=6)
        self.A8.grid(row=0,column=7)
        self.A9.grid(row=0,column=8)
        self.A10.grid(row=0,column=9)
        self.A11.grid(row=0,column=10)
        self.A12.grid(row=0,column=11)
        self.A13.grid(row=0,column=12)
        self.A14.grid(row=0,column=13)
        self.A15.grid(row=0,column=14)
        self.A16.grid(row=0,column=15)

     	self.B1.grid(row=1,column=0)
        self.B2.grid(row=1,column=1)
        self.B3.grid(row=1,column=2)
        self.B4.grid(row=1,column=3)
        self.B5.grid(row=1,column=4)
        self.B6.grid(row=1,column=5)
        self.B7.grid(row=1,column=6)
        self.B8.grid(row=1,column=7)
        self.B9.grid(row=1,column=8)
        self.B10.grid(row=1,column=9)
        self.B11.grid(row=1,column=10)
        self.B12.grid(row=1,column=11)
        self.B13.grid(row=1,column=12)
        self.B14.grid(row=1,column=13)
        self.B15.grid(row=1,column=14)
        self.B16.grid(row=1,column=15)

        self.C1.grid(row=2,column=0)
        self.C2.grid(row=2,column=1)
        self.C3.grid(row=2,column=2)
        self.C4.grid(row=2,column=3)
        self.C5.grid(row=2,column=4)
        self.C6.grid(row=2,column=5)
        self.C7.grid(row=2,column=6)
        self.C8.grid(row=2,column=7)
        self.C9.grid(row=2,column=8)
        self.C10.grid(row=2,column=9)
        self.C11.grid(row=2,column=10)
        self.C12.grid(row=2,column=11)
        self.C13.grid(row=2,column=12)
        self.C14.grid(row=2,column=13)
        self.C15.grid(row=2,column=14)
        self.C16.grid(row=2,column=15)

        self.D1.grid(row=3,column=0)
        self.D2.grid(row=3,column=1)
        self.D3.grid(row=3,column=2)
        self.D4.grid(row=3,column=3)
        self.D5.grid(row=3,column=4)
        self.D6.grid(row=3,column=5)
        self.D7.grid(row=3,column=6)
        self.D8.grid(row=3,column=7)
        self.D9.grid(row=3,column=8)
        self.D10.grid(row=3,column=9)
        self.D11.grid(row=3,column=10)
        self.D12.grid(row=3,column=11)
        self.D13.grid(row=3,column=12)
        self.D14.grid(row=3,column=13)
        self.D15.grid(row=3,column=14)
        self.D16.grid(row=3,column=15)
        self.start_button.grid(row=5,column=3,columnspan=4)
        self.stop_button.grid(row=5,column=8,columnspan=4)


    def aStr(self,R,G,B):  # Este metodo funciona para convertir las temperaturas HeX a un string
        str="#"
        strx=""
        stry=""
        strz=""
        x=hex(R)
        if (x == "0x0"):
                strx= x+'0'
	elif (x == "0x1" or x == "0x2" or x == "0x3" or x == "0x4" or x == "0x5" or x == "0x6" or x == "0x7" or x == "0x8" or x == "0x9" or x == "0xa" or x == "0xb" or x == "0xc" or x == "0xd" or x == "0xe" or x == "0xf"):
                strx=x.replace('0x','')
                strx = '0'+ strx
        else:
                strx=x


        y=hex(G)
        if (y == "0x0"):
                stry=y+'0'
        if (y == "0x0"):
                stry=y+'0'
        elif (y == "0x1" or y == "0x2" or y == "0x3" or y == "0x4" or y == "0x5" or y == "0x6" or y == "0x7" or y == "0x8" or y == "0x9" or y == "0xa" or y == "0xb" or 
y == "0xc" or y == "0xd" or y == "0xe" or y == "0xf"):
                stry=y.replace('0x','')
                stry = '0'+ stry
        else:
                stry=y



        z=hex(B)
        if (z == "0x0"):
                strz=z+'0'
        elif (z == "0x1" or z == "0x2" or z == "0x3" or z == "0x4" or z == "0x5" or z == "0x6" or z == "0x7" or z == "0x8" or z == "0x9" or z == "0xa" or z == "0xb" or 
z == "0xc" or z == "0xd" or z == "0xe" or z == "0xf"):
                strz=z.replace('0x','')
                strz = '0'+ strz
        else:
                strz=z

        str+=(strx+stry+strz)

        str=str.replace('0x','')

        return str



    def Calculo_de_resolucion(self): # Metodo que calcula la resolucion 
        return 1500/self.MaxTemp


    def Calculo_de_rango_de_color(self): # Metodo que calcula el rango de cada color dependiendo de la temperatura recibida
        return self.MaxTemp/12

    def aHex(self,x): # Metodo para cambiar los valores recibidos a valores en hexadecimal, eso va a variar dependiendo de la resolucion y el rango de color
        self.resolucion=self.Calculo_de_resolucion()
        self.rango_de_color=self.Calculo_de_rango_de_color()
        str=''
        hex=[]
        R=0
        G=0
        B=0
        for temperatura in x:
                if ( 0<= temperatura <=self.rango_de_color):
                        R=int((125-self.resolucion*temperatura))
                        G=0
                        B=255
                        str=self.aStr(R,G,B)
                        hex.append(str)

                if (self.rango_de_color+1<= temperatura <=2*self.rango_de_color):
                        R=0
                        G=int((temperatura%self.rango_de_color)*self.resolucion)
                        B=255
                        str=self.aStr(R,G,B)
                        hex.append(str)

                if (2*self.rango_de_color+1<= temperatura <=3*self.rango_de_color):
                        R=0
                        G=int(125+(temperatura%self.rango_de_color)*self.resolucion)
                        B=255
                        str=self.aStr(R,G,B)
                        hex.append(str)

                if (3*self.rango_de_color+1<= temperatura<=4*self.rango_de_color):
                        R=0
                        G=0
                        B=int(250-(temperatura%self.rango_de_color)*self.resolucion)
                        str=self.aStr(R,G,B)
                        hex.append(str)

                if (4*self.rango_de_color+1<= temperatura <=5*self.rango_de_color):
                        R=0
                        G=255
                        B=int(125-(temperatura%self.rango_de_color)*self.resolucion)
                        str=self.aStr(R,G,B)
                        hex.append(str)

                if (5*self.rango_de_color+1<= temperatura <=6*self.rango_de_color):
                        R=int((temperatura%self.rango_de_color)*self.resolucion)
                        G=255
                        B=0
                        str=self.aStr(R,G,B)
                        hex.append(str)

                if (6*self.rango_de_color+1<= temperatura<=7*self.rango_de_color):
                        R=int(125+(temperatura%self.rango_de_color)*self.resolucion)
                        G=255
                        B=0
                        str=self.aStr(R,G,B)
                        hex.append(str)
                
                if (7*self.rango_de_color+1<= temperatura <=8*self.rango_de_color):
                        R=255
                        G=int(250-(temperatura%self.rango_de_color)*self.resolucion)
                        B=0
                        str=self.aStr(R,G,B)
                        hex.append(str)

                if (8*self.rango_de_color+1<= temperatura <=9*self.rango_de_color):
                        R=255
                        G=int(125-(temperatura%self.rango_de_color)*self.resolucion)
                        B=0
                        str=self.aStr(R,G,B)
                        hex.append(str)

                if (9*self.rango_de_color+1<= temperatura <=10*self.rango_de_color):
                        R=255
                        G=0
                        B=int((temperatura%self.rango_de_color)*self.resolucion)
                        str=self.aStr(R,G,B)
                        hex.append(str)
                if (10*self.rango_de_color+1<= temperatura <=11*self.rango_de_color):
                        R=255
                        G=0
                        B=int(125+(temperatura%self.rango_de_color)*self.resolucion)
                        str=self.aStr(R,G,B)
                        hex.append(str)

                if (11*self.rango_de_color+1<= temperatura <=12*self.rango_de_color):
                        R=255
                        G=0
                        B=int(250-(temperatura%self.rango_de_color)*self.resolucion)
                        str=self.aStr(R,G,B)
                        hex.append(str)

        return hex

    def start_blinking(self): # Metodo para hechar a andar el programa
        self.do_blink = True
        self.blink()

    def stop_blinking(self):  # Metodo para parar el programa
        self.do_blink = False

    def blink(self):   # Una vez hechado a andar el programa se ejecuta este metodo, y es aqui donde los colores de cada canvas se ve modificado dependiendo la temp.
        if self.do_blink:
            proyecto = ""
            str = ""
            proyecto= self.ser.readline()
            while (proyecto != '500.00\r\n'):
                proyecto = self.ser.readline()
            proyecto = self.ser.readline()
            while (proyecto != '500.00\r\n'):
                proyecto = proyecto.replace("\r\n","")
                proyecto = proyecto.replace(" ","")
                str+=proyecto
                proyecto= int(float(str))
                self.valor.append(proyecto)
                str=""
                proyecto =self.ser.readline()


            new_color = self.aHex(self.valor)

            if len(new_color) == 64:
                self.A1.config(bg =new_color[0])
                self.B1.config(bg =new_color[1])
                self.C1.config(bg =new_color[2])
                self.D1.config(bg =new_color[3])
                self.A2.config(bg =new_color[4])
                self.B2.config(bg =new_color[5])
                self.C2.config(bg =new_color[6])
                self.D2.config(bg =new_color[7])

                self.A3.config(bg =new_color[8])
                self.B3.config(bg =new_color[9])
                self.C3.config(bg =new_color[10])
                self.D3.config(bg =new_color[11])

                self.A4.config(bg =new_color[12])
                self.B4.config(bg =new_color[13])
                self.C4.config(bg =new_color[14])
                self.D4.config(bg =new_color[15])

                self.A5.config(bg =new_color[16])
                self.B5.config(bg =new_color[17])
                self.C5.config(bg =new_color[18])
                self.D5.config(bg =new_color[19])

                self.A6.config(bg =new_color[20])
                self.B6.config(bg =new_color[21])
                self.C6.config(bg =new_color[22])
                self.D6.config(bg =new_color[23])

                self.A7.config(bg =new_color[24])
                self.B7.config(bg =new_color[25])
                self.C7.config(bg =new_color[26])
                self.D7.config(bg =new_color[27])

                self.A8.config(bg =new_color[28])
                self.B8.config(bg =new_color[29])
                self.C8.config(bg =new_color[30])
                self.D8.config(bg =new_color[31])

                self.A9.config(bg =new_color[32])
                self.B9.config(bg =new_color[33])
                self.C9.config(bg =new_color[34])
                self.D9.config(bg =new_color[35])

                self.A10.config(bg =new_color[36])
                self.B10.config(bg =new_color[37])
                self.C10.config(bg =new_color[38])
                self.D10.config(bg =new_color[39])

                self.A11.config(bg =new_color[40])
                self.B11.config(bg =new_color[41])
                self.C11.config(bg =new_color[42])
                self.D11.config(bg =new_color[43])

                self.A12.config(bg =new_color[44])
                self.B12.config(bg =new_color[45])
                self.C12.config(bg =new_color[46])
                self.D12.config(bg =new_color[47])

                self.A13.config(bg =new_color[48])
                self.B13.config(bg =new_color[49])
                self.C13.config(bg =new_color[50])
                self.D13.config(bg =new_color[51])

                self.A14.config(bg =new_color[52])
                self.B14.config(bg =new_color[53])
                self.C14.config(bg =new_color[54])
                self.D14.config(bg =new_color[55])

                self.A15.config(bg =new_color[56])
                self.B15.config(bg =new_color[57])
                self.C15.config(bg =new_color[58])
                self.D15.config(bg =new_color[59])
                self.A16.config(bg =new_color[60])
                self.B16.config(bg =new_color[61])
                self.C16.config(bg =new_color[62])
                self.D16.config(bg =new_color[63])

            for i in range(len(self.valor)):
                self.valor.pop()

            self.after(50, self.blink)

if __name__ == "__main__":
    root = MyApp()
    root.mainloop()


