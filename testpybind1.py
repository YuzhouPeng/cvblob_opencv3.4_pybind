import sys
sys.path.insert(0,"./algorithm/after_proc_algo/cvblob/lib")
sys.path.append("../cvblob/lib")
import test1

import cv2,time

def returnblobresults(input1,row,col):
    p = test1.outvalue(input1,row,col)
    # print(p)
    return p


# test = cv2.imread("/home/sycv/workplace/pengyuzhou/el_webservice/algorithm/after_proc_algo/result6.jpg")
# time1 = time.time()
# returnblobresults(test,340,169)
# time2 = time.time()
# print("time cost {}".format(time2-time1))