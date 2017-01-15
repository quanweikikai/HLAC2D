import numpy as np
import cv2 as cv
import matplotlib.pyplot as plt

masks = [0b000010000,0b000011000,0b001010000,0b010010000,0b100010000,
                0b000111000,0b001010100,0b010010010,0b100010001,0b001110000,
                0b010010100,0b100010010,0b000110001,0b000011100,0b001010010,
                0b010010001,0b100011000,0b010110000,0b100010100,0b000110010,
                0b000010101,0b000011010,0b001010001,0b010011000,0b101010000]

def IMG2BIN(cell):
    binNum = 0
    for i in xrange(3):
        for j in xrange(3):
            if not cell[i,j] == 0:
                binNum = binNum << 1
                binNum += 1
            else:
                binNum = binNum << 1
    return binNum



def HLAC_2D(img):
    feature = []
    imgShape = img.shape
    if len(imgShape) == 3 and imgShape[2] == 3:
        img = cv.cvtColor(img,cv.COLOR_RGB2GRAY)

    count = [0 for i in xrange(len(masks))]
    for row in xrange(imgShape[0]-2):
        for col in xrange(imgShape[1]-2):
            cell = img[row:row+3, col:col+3]
            binNum = IMG2BIN(cell)
            for idx in xrange(len(masks)):
                if (binNum & masks[idx]) == masks[idx]:
                    count [idx] += 1

    return count

def zoomIMG(img,multiplier):
    imgShape = img.shape
    if multiplier > 1:
        outputIMG = np.zeros((imgShape[0]*multiplier,imgShape[1]*multiplier))
        for row in xrange(imgShape[0]):
            for col in xrange(imgShape[1]):
                if not img[row,col] == 0:
                    outputIMG[row*multiplier:(row+1)*multiplier, col*multiplier:(col+1)*multiplier] = 1
    elif multiplier < 1:
        assert 1/multiplier ==  int(1/multiplier), "error"
        assert imgShape[0]*multiplier ==  int(imgShape[0]*multiplier), "error"
        assert imgShape[1]*multiplier ==  int(imgShape[1]*multiplier), "error"
        output_row = int(imgShape[0]*multiplier)
        output_col = int(imgShape[1]*multiplier)
        outputIMG = np.zeros((output_row,output_col))
        cell_side = int(1/multiplier)
        for x in xrange(output_row):
            for y in xrange(output_col):
                cell_sum = np.nonzero(img[x*cell_side:(x+1)*cell_side,y*cell_side:(y+1)*cell_side])[0].shape[0]
                if cell_sum >= cell_side**2 * 0.5:
                    outputIMG[x,y] = 1
    return outputIMG
        




if __name__ == "__main__":
    img = cv.imread('form.jpg')
    img = cv.cvtColor(img,cv.COLOR_RGB2GRAY)
    CVimg = cv.resize(img,(40,40))
    img = zoomIMG(img,0.1)
    L_img = zoomIMG(img,10)
    L_img_CV = zoomIMG(CVimg,10)
    plt.imshow(L_img)
    plt.show()
    plt.imshow(L_img_CV)
    plt.show()
    cnt = HLAC_2D(img)
    cnt1 = HLAC_2D(CVimg)
    print cnt
    print cnt1
