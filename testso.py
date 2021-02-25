import ctypes
ll = ctypes.cdll.LoadLibrary   
lib = ll("./lib/libcvbloblib.so")
lib.main()
