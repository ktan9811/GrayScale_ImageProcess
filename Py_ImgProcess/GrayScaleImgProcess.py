from tkinter import *
from tkinter import messagebox
from tkinter.filedialog import *
from tkinter.simpledialog import *
import MyImgProcess as mcv2
import os.path
import math
import struct

## Var
global window, canvas, paper
inImage = mcv2.IMG()
outImage = mcv2.IMG()


## GUI function
def openImage():
    global window, canvas, paper
    global inImage, outImage, root

    root = askopenfilename(parent=window, filetypes=(('RAW file', '*.raw'),('file','*.*')))
    
    fsize = os.path.getsize(root)

    inH = inImage.H = int(math.sqrt(fsize))
    inW = inImage.W = int(math.sqrt(fsize))
    
    inImage.px = mcv2.malloc2D(inH, inW)
    
    rfp = open(root, 'rb')
    for y in range(inH):
        for x in range(inW):
            inImage.px[y][x] = ord(rfp.read(1))

    rfp.close()
    displayImage(inImage)
    
def saveImage() :
    global window, canvas, paper
    global inImage, outImage
    
    outH = outImage.H
    outW = outImage.W
    
    if (outImage == None or outImage.H==0) : return
    
    wfp = asksaveasfile(parent=window, mode='wb', defaultextension='*.raw',
                        filetypes=(('RAW file', '*.raw'), ('All file', '*.*'))  )

    for i in range(outH) :
        for k in range(outW) :
            wfp.write( struct.pack('B', outImage[i][k]) )
    wfp.close()
    messagebox.showinfo('성공', wfp.name + ' 저장완료!')

def displayImage(img):
    global window, canvas, paper

    if (canvas != None): canvas.destroy()

    inH = img.H
    inW = img.W
    
    #윈도우 사이즈 조절
    window.geometry(str(inH)+'x'+str(inW))
    canvas = Canvas(window, height=inH, width=inW, bg='yellow') 
    paper = PhotoImage(height=inH, width=inW) 
    canvas.create_image((inH // 2, inW // 2), image=paper, state='normal')
    
    #출력
    rgbString = "" 
    for y in range(inH) :
        oneString = "" 
        for x in range(inW) :
            r = g = b = img.px[y][x]
            oneString += '#%02x%02x%02x ' % (r, g, b)
        rgbString += '{' + oneString + '} '
    paper.put(rgbString)
    canvas.pack()

## My CV
    ## 화소점
def addImage():
    value = askinteger('정수입력','-255~255 입력', maxvalue=255, minvalue=-255)
    outImage = mcv2.AddImg(inImage, value)
    displayImage(outImage)

def invImage():
    outImage = mcv2.InvImg(inImage)
    displayImage(outImage)
    
def gammaImage():
    value = askfloat("Gamma","Value : 0.2 ~ 1.8", maxvalue=1.8, minvalue=0.2)
    outImage = mcv2.GammaImg(inImage, value) 
    displayImage(outImage)
    
    ## 히스토그램
def histStretchImage():
    outImage = mcv2.HistStretch(inImage)
    displayImage(outImage)
    
    
    ## 좌표 변환
def reverseXImage():
    outImage = mcv2.RotateX(inImage)
    displayImage(outImage)
    
def rotateImage():
    value = askinteger("Degree","Value : 0 ~ 360", maxvalue=360, minvalue=0)
    outImage = mcv2.RotateImg(inImage, value) 
    displayImage(outImage)
    
    

    ## 화소 영역
def blurImage():
    k = askinteger('커널 사이즈','0~10 입력', maxvalue=10, minvalue=1)
    outImage = mcv2.BlurImg(inImage, k)
    displayImage(outImage)

def embossImage():
    k = askinteger('커널 사이즈','0~10 입력', maxvalue=10, minvalue=1)
    outImage = mcv2.EmbossImg(inImage, k)
    displayImage(outImage)


def main():
    global window, canvas, paper
    window, canvas, paper = None, None, None
    window = Tk()
    window.geometry("512x512")
    window.resizable(False, False)
    window.title("GrayScale ImgProcess with python")

    canvas = Canvas(window, height=256, width=256)
    paper = PhotoImage(height=256, width=256)
    canvas.create_image((256//2, 256//2), image=paper, state='normal')

    # Menu 생성
    mainMenu = Menu(window)
    window.config(menu=mainMenu)

    fileMenu = Menu(mainMenu, tearoff=0)
    mainMenu.add_cascade(label='File', menu=fileMenu)
    fileMenu.add_command(label='Open', command=openImage)
    fileMenu.add_command(label='Save', command=saveImage)
    fileMenu.add_separator()
    fileMenu.add_command(label='Close')

    pixelMenu = Menu(mainMenu, tearoff=0)
    mainMenu.add_cascade(label='Pixel', menu=pixelMenu)
    pixelMenu.add_command(label='Add', command=addImage)
    pixelMenu.add_command(label='Inverse', command=invImage)
    pixelMenu.add_command(label='Gamma', command=gammaImage)
    pixelMenu.add_command(label='Hist St', command=histStretchImage)

    transMenu = Menu(mainMenu, tearoff=0)
    mainMenu.add_cascade(label='Transformation', menu=transMenu)
    transMenu.add_command(label='Reverse X', command=reverseXImage)
    transMenu.add_command(label='Rotate', command=rotateImage)

    convolMenu = Menu(mainMenu, tearoff=0)
    mainMenu.add_cascade(label='convolution', menu=convolMenu)
    convolMenu.add_command(label='Blur', command=blurImage)
    convolMenu.add_command(label='Emboss', command=embossImage)
    
    canvas.pack()
    window.mainloop()
    return

if (__name__ == "__main__"):
    main()