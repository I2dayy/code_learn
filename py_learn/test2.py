import cv2 #opencv读取的格式为BGR
import matplotlib.pyplot as plt
import numpy as np
import os

#读取视频
vc = cv2.VideoCapture('D:\\Study\\dai_ma\\py\\picture\\test.mp4')

if vc.isOpened():
    open, frame = vc.read()
else:
    open = False

while open:
    ret, frame = vc.read()
    if frame is None:
        break
    if ret == True:
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        cv2.imshow('result', gray)
        if cv2.waitKey(50) & 0xFF == 27:
            break

vc.release()
cv2.destroyAllWindows()
