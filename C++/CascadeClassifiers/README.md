### Create Samples
``` bash
$ opencv_createsamples -img circle.jpg -num 50 -bg negatives.dat -vec circles.vec -maxxangle 0.6 -maxyangle 0 -maxzangle 0.3 -maxidev 100 -bgcolor 0 -bgthresh 0 -w 100 -h 100
```

### View Samples
``` bash
opencv_createsamples -vec circles.vec -w 100 -h 100
```

### Training the Classifier
``` bash
$ opencv_traincascade -data classifier -vec circles.vec -bg negatives.dat -numStages 20 -minHitRate 0.999 -maxFalseAlarmRate 0.5 -numPos 50 -numNeg 20 -w 100 -h 100 -mode ALL -precalcValBufSize 1024 -precalcIdxBufSize 1024
```

