import ctypes
import cv2

class StructPointer(ctypes.Structure):
    _fields_ = [("width", ctypes.c_int),
    ("height", ctypes.c_int),
    ("centeriodx", ctypes.c_int),
    ("centeriody", ctypes.c_int),
    ("longedge", ctypes.c_int),
    ("area", ctypes.c_int)]
    def __init__(self,arrays):


ll = ctypes.cdll.LoadLibrary   
lib = ll("/home/sycv/workplace/pengyuzhou/cvblob/lib/libtestlib1.so")
lib.blobdet.restype = ctypes.POINTER(StructPointer)
p = lib.blobdet()
# print(len(p))
# print(p.content.area)
