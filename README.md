# FFilter

[![Build Status](https://travis-ci.org/iamantony/FFilter.svg?branch=master)](https://travis-ci.org/iamantony/FFilter)

Author: [Antony Cherepanov][mypage]  
E-mail: antony.cherepanov@gmail.com

FFilter is an app that can be used for studing different types of noise
generators / noise filters in image processing. Currently only filtration
of grayscale images are supported.

Tested on Ubuntu 12.04 with gcc 4.6.3, Qt 4.8 and higher.

## Build
```bash
cd /path/to/folder/with/FFilter
qmake -r
make
```

## How to use

Main window of the app consists of the following elements (downward from left
to right):
- menu bar
- three image labels for original, noisy and filtered images
- button "Open image" for loading original image
- buttons for saving noisy and filtered images
- slider for setting noise level
- label that show standard deviation value
- button "Filter image" that start filtration process
- progress bar

First of all, you need to _**load an image**_ to which you will be working.
Click "Open image" button and choose image. This image will be loaded in all
three image labels. If you pick color image, FFilter will transform it to
greyscale image.

Next you can _**set noise settings**_. Go to Menu -> Noise -> Noise settings.
In opened window "Noise Settings" you can choose noise type and noise
amplitude (AMP):
- if you choose *Constant* noise type, then algorithm will choose N pixels
and add to their luminance AMP value
- if you choose *Random* noise type, then algorithm will choose N pixels
and add to their luminance random value within [0, AMP]
- if you choose *Absolute Random* noise type, then algorithm will choose
N pixels and add to their luminance some random value within [0, MAX_LUM]

With the slider "Noise level" you can choose how many pixels (in percents)
will be noised. The result noisy image will be set to the central (second)
image label.

Let's move to _**filtration section**_. Go to Menu -> Filter -> Filter mask
settings. In opened window "Mask settings" you can _**set mask parameters**_.
Mask is a collection of pixels, that are involved in filtration process.
Each mask must have one central pixel (colored red in mask) - this is the
pixel that is currently processing. Also mask can contain other pixels -
neighbors of the central pixel. Also each mask pixel can have "weight".
This value helps filtration algorithm to understand importance of the pixel.

In "Mask settings" dialog you can set the size of the mask (number of rows
and columns). By clicking the right mouse button on the mask cell you will
call its' context menu. In context menu you can enable/disable pixel
or set it as central pixel. To set "weight" for the enabled pixel,
click the left mouse button on the mask cell and edit its value.

*Example mask*: set mask size 3 x 3. Central pixel - pixel with 
coordinates [2, 2]. Enable all pixels in mask and set for all of them
weight "1".

To set _**filtration method**_, go to Menu -> Filter -> Aggregation filter
settings. In opened dialog "Filter settings" you can set type of
aggregation operator. What is aggregation operator? This is the function
that gives the filtered value for the pixel. The calculation is made on the
basis of mask parameters. Let's consider the available operators:
- Min - this operator will choose mask pixel with minimum value (luminance)
- Max - this operator will choose mask pixel with maximum value
- Mean - this operator will calc mean value of the mask pixels. For this
aggregation operator you can set "power" parameter. Value of each mask pixel
will be raised to the defined power before final calculation of mean value.
- Geometric Mean - this operator will calc [geometric mean][geomean] value
of the mask pixels
- Harmonic Mean - this operator will calc [harmonic mean][harmmean] value
of the mask pixels
- Medain - this operator will choose mask pixel with mean value
- Functional - this operator will calc function (natural logarithm or
exponent) for each mask pixel, summ all results and then calc inverse
function

After you setup all parameters, you can start filtration process by
clicking on "Filter image" button. Filtered image will be set on the right
(third) image label.

[mypage]: https://github.com/iamantony
[geomean]: https://en.wikipedia.org/wiki/Geometric_mean
[harmmean]: https://en.wikipedia.org/wiki/Harmonic_mean
