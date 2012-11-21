#ifndef MASK_H
#define MASK_H

namespace Mask
{
	// Use this struct to describe each pixel in mask
	//
	// Mask - it's a set of pixels. Each mask has one "central" pixel and several of his neighbors. Size of mask
	// could be set by params: ROWS_IN_MASK and COLUMS_IN_MASK.
	//
	// Position of "central" pixel is not always equal to coordinates of geometric center of mask. In general,
	// any pixel of mask could be setted as "central" pixel. So, that is why we need parameter isCentral.
	//
	// Shape of mask is not predefined. It could be a cross, a plus, a square, a circle or even has an amorphous shape.
	// So, how we could define position of all pixels in mask? Well, we have "central" pixel. Let define his coord
	// in mask as [0, 0]. His right neighbor pixel has coord [1, 0]. And pixel at top of "central" pixel has coords
	// [0, 1]. These coords could be interpret as offset from "central" pixel. Let's save these offsets to params
	// offsetX and offsetY.
	//
	// "Central" pixel is individual. He has kinda relationships with all his neighbor pixels (and they individuals
	// too). Some of these pixels are important for him (let's say they like a good friends of him). And some of them
	// are not important or even unpleasant. Moreover, "central" pixel could be a narcissus (he proud of himself)
	// or a very depressed guy (he hate himself and can't find meaning of life). To describe all these relationships
	// we could use parameter weight.

#define ROWS_IN_MASK 7
#define COLUMS_IN_MASK 7

	struct MasksPixel
	{
		bool isEnabled;
		bool isCentral;
		int offsetX;
		int offsetY;
		long double weight;
	};
}

#endif // MASK_H
