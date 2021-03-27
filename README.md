# cvblob_opencv3.4
This is a cvblob(blob detection) project inheried from cvblob, which could detect mutiple shapes from images. Adding pybind11 binding so it could be used in python scripts.

# requirements

TensorRT 7.0 (you need to install tensorrt first)<br>
Python3.7<br>
opencv 4.4<br>
cmake 3.18<br>
# train .pth file and convert .wts

## create env

```
pip install -r requirements.txt
```

## train .pth file

train your dataset by following [pytorch-unet](https://github.com/milesial/Pytorch-UNet) and generate .pth file.<br>

## convert .wts

run gen_wts from utils folder, and move it to project folder (you need to run with east training environment)(<br>

# generate engine file and infer

## create build folder in project folder
```
mkdir build
```

## make file, generate exec file
```
cd build
cmake ..
make
```

## generate TensorRT engine file and infer image
```
unet -s
```
then a unet exec file will generated, you can use unet -d to infer files in a folder<br>
```
unet -d ../samples
```

# efficiency
the speed of tensorRT engine is much faster

 pytorch | TensorRT FP32 | TensorRT FP16
 ---- | ----- | ------  
 816x672  | 816x672 | 816x672 
 58ms  | 43ms (batchsize 8) | 14ms (batchsize 8) 


# Further development

1. add INT8 calibrator<br>
2. add custom plugin<br>
etc
