# Install chainer with GPU support

## remove existent chainer (optional)
```
pip uninstall chainer
```

## get code
```
git clone https://github.com/pfnet/chainer
```

## install nvidia libs
* [CUDA sdk](https://developer.nvidia.com/cuda-downloads)
* [cuDNN sdk](https://developer.nvidia.com/cudnn)
* copy cuDNN files to `c:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v8.0\`

## install python libs
* conda install numpy
* conda install six
* conda install pillow
* conda install cython

## Visual Studio settings
Add `c:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\` to `PATH` in environment variables.

## build chainer
```
cd chainer
python setup.py	install
```

# Install chainer-fast-neuralstyle

## get code
```
git clone https://github.com/yusuketomoto/chainer-fast-neuralstyle
```

## run
```
python generate.py sample_images/tubingen.jpg -m models/seurat.model -o sample_images/output.jpg -g 0
```

## train
```
python train.py -s <style_image_path> -d <training_dataset_path> -g 0
```
## problem

cudaErrorMemoryAllocation: out of memory

solution: use a smaller image.

