FFilter is an app can be used for study different types of noise filters in image processing or actually for image
filtering. Currently only grayscale images are supported.

Features:

1. Mask constructor.
Filtration is performed for each pixel in the image. Quality of this process depends on several aspects. One of
them is structure of mask. Mask is a collection of pixels, that involved in filtration. They help the algorith
to set appropriate color (or luminance) for image pixels.

Each mask must have one central pixel (colored red) - this is pixel that currently processing. If mask has only one
activated pixel (central), filtrated image will be a copy of original noised image. If we want to filter image, we
sholuld activate (enable) some pixel-neighbors of the central pixel in mask. Also we can set weights to enabled
pixels.

2. Aggregation Operators
Aggregation Operators are core of filtration process. Their function is to choose from mask best pixel using some rule.
Params of choosed pixel will be then set as parameters of central pixel.

3. Noise types
For study characteristics of different types of aggregation operators we sholud have some types of noise generators.
They artificially transform the original image selected by the user, in the noisy image.
