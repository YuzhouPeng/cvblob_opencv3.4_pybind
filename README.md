# cvblob_opencv3.4
This is a cvblob(blob detection) project inheried from cvblob, which could detect mutiple shapes from images and return properties (minarearect, centroids, long edge, etc). Adding pybind11 binding so it could be used in python scripts.<br>
![1](https://user-images.githubusercontent.com/13601004/113385786-61911e80-93bb-11eb-9902-d54bb13522d4.png)

# requirements
ubuntu16.04<br>
pybind11<br>
opencv 3.4<br>
cmake 3.18<br>
# train .pth file and convert .wts

## install opencv

install opencv3.4 in your computer and add path to LD_LIBRARY_PATH.<br>

## create env

```
pip install -r cvblob_requirements.txt
```


## make file, generate test file
```
cmake .
make
```

## run test script and show result
```
cd bin
```
then a test exec file will generated, it will inter test.png in test folder and show blobs<br>
```
./test
```



# pybind11 binding and ctypes binding
dependency is shown in root dir CMakeLists.txt<br>
run function in testpybind1.py to test pybind function<br>
