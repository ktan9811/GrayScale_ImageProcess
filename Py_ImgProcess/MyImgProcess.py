import random as rd
import math

class IMG:
    def __init__(self):
        px = []
        self.H = 0
        self.W = 0

def malloc2D(H, W):
    memory = [[0 for _ in range(W)]for _ in range(H)]
    return memory

def ImgLoad(img):
    IMG = [[rd.randint(0, 255) for _ in range(img.W)]for _ in range(img.H)]
       
    return IMG

def EqualImg(src):
    img = IMG()
    img.H = src.H
    img.W = src.W
    img.px = malloc2D(src.H, src.W)
    
    for y in range(src.H):
        for x in range(src.W):
            img.px[y][x] = src.px[y][x]
            
    return img
## 화소점 처리
def AddImg(src, val):
    img = EqualImg(src)

    for y in range(src.H):
        for x in range(src.W):
            img.px[y][x] += val
            if img.px[y][x] > 255: img.px[y][x] = 255
            elif img.px[y][x] < 0: img.px[y][x] = 0
            
    return  img

def InvImg(src):
    img = EqualImg(src)
    
    for y in range(src.H):
        for x in range(src.W):
            img.px[y][x] = 255 - img.px[y][x]

    return img

def GammaImg(src, val):
    img = EqualImg(src)
    
    for y in range(src.H):
        for x in range(src.W):
            img.px[y][x] = (int)(255 * (img.px[y][x] / 255)**val)

    return img

## 히스토그램
def HistStretch(src):
    img = EqualImg(src)
    
    HIGH , LOW = 0, 255
    for y in range(int(src.H)):
        for x in range(int(src.W)):
            if (HIGH > img.px[y][x]): HIGH = img.px[y][x]
            if (LOW < img.px[y][x]): LOW = img.px[y][x]
    
    for y in range(int(src.H)):
        for x in range(int(src.W)):
            img.px[y][x] = int((src.px[y][x] - LOW) / (HIGH - LOW) * 255)
            
    return  img

## 좌표 변환
def RotateX(src):
    img = EqualImg(src)
    
    for y in range(int(src.H)):
        for x in range(int(src.W/2)):
            img.px[y][x], img.px[y][img.W - x - 1] = img.px[y][img.W - x - 1], img.px[y][x]
            
            
    return  img

def RotateImg(src, val):
    img = EqualImg(src)
    
    radian = -val *3.141592 / 180.0
    
    cx = img.H / 2
    cy = img.H / 2
    
    for y in range(src.H):
        for x in range(src.W):
            xd = y
            yd = x
            
            xs = math.cos(radian) * (xd - cx) + math.sin(radian) * (yd - cy)
            ys = math.cos(radian) * (yd - cy) - math.sin(radian) * (xd - cx)
            xs += cx
            ys += cy
            
            xs = int(xs)
            ys = int(ys)
            
            if((0 <= xs and xs < img.H) and (0 <= ys and ys < img.W)):
                img.px[xd][yd] = src.px[xs][ys]

    return img

## 화소 영역 처리

def setBlurMask(k):
    mask = malloc2D(k, k)
    for y in range (k):
        for x in range (k):
            mask[y][x] = 1/k/k

    return mask

def BlurImg(src, K):
    if(K % 2 == 0) : K += 1
    
    img = EqualImg(src)
    mask = setBlurMask(K)
    inTemp = malloc2D(src.H + K - 1, src.W + K - 1)
    for y in range(int(src.H + K - 1)):
        for x in range(int(src.W + K - 1)):
            inTemp[y][x] = 127
    
    for y in range(int(K/2), src.H + int(K/2)):
        for x in range(int(K/2), src.W + int(K/2)):
            inTemp[y][x] = src.px[y - (int)(K/2)][x - (int)(K/2)]
                                  
    for y in range (src.H):
        for x in range (src.W):
            S = 0.0
            for i in range(K):
                for j in range(K):
                    S += mask[i][j] * inTemp[y+i][x+j]
            img.px[y][x] = int(S) 
            
    return  img


def setEmbossMask(k):
    mask = malloc2D(k, k)
    for y in range (k):
        for x in range (k):
            if (y > x) : mask[y][x] = 1
            elif (y < x) : mask[y][x] = -1
            else : mask[y][x] = 0

    return mask

def EmbossImg(src, K):
    if(K % 2 == 0) : K += 1
    
    img = EqualImg(src)
    mask = setEmbossMask(K)
    inTemp = malloc2D(src.H + K - 1, src.W + K - 1)
    
    for y in range(int(src.H + K - 1)):
        for x in range(int(src.W + K - 1)):
            inTemp[y][x] = 127
    
    for y in range(int(K/2), src.H + int(K/2)):
        for x in range(int(K/2), src.W + int(K/2)):
            inTemp[y][x] = src.px[y - (int)(K/2)][x - (int)(K/2)]
                                  
    for y in range (src.H):
        for x in range (src.W):
            S = 0.0
            for i in range(K):
                for j in range(K):
                    S += mask[i][j] * inTemp[y+i][x+j]
            img.px[y][x] = int(S) 
            
    for y in range (src.H):
        for x in range (src.W):
            img.px[y][x] += 127
            if (img.px[y][x] > 255) : img.px[y][x] = 255
            if (img.px[y][x] < 0) : img.px[y][x] = 0
    return  img