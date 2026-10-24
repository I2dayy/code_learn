import cv2 #opencv读取的格式为BGR
import matplotlib.pyplot as plt
import numpy as np
import os

#读取图片
""" 显示图像函数
def cv_show(name,imge):
    img=cv2.imread(imge)
    cv2.imshow(name,img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

cv_show('image','D:\Study\dai_ma\py\picture\BJpnj.png')
"""
img=cv2.imread('D:\Study\dai_ma\py\picture\BJpnj.png',cv2.IMREAD_GRAYSCALE) #灰白
cv2.imshow('image',img) #图像的显示，也可创建多个窗口
cv2.waitKey(0) #等待时间，毫秒级，0表示任意键终止
cv2.destroyAllWindows()

#保存 cv2.imwrite('保存路径',保存的图片，如img)
