accelerateExample
=================

#about

example of using openframeworks w/ apple's accelerate framework

![image](https://raw.github.com/ofZach/accelerateExample/master/accelerateExample.png)

this example generates 100,000 random shapes with 256 points each,  using sin and cos (with random angle speeds, etc) and finds the one closest to a straight line, a shape with x increaing linearly and y constant.  It uses apple's accelerate framework to do the math, grouping all the data into giant vectors for subtraction, distance and mean calculation. 

I've seen speed ups against by hand calculation of 400% (for non optimized code) to 150% against fully optimized (unroll loops, -O3)…  helpful if you are doing alot of crunching. 

# todo: 

* a proper test suite, trying the accelerate code vs by hand for different quantities
* make some attempts to optimize the by hand (pointer math, etc)

#### note: 

one oddity is that I've seen this take a really long time the first couple of calculations then be a consistant 200 milliseconds or so -- I wonder if there's some sort of allocation that happens or that I'm not doing right.  After the first couple of solves (which can be as high as five seconds) it is consistant and seems pretty fast. Noticed this also with the by hand code, so I'm not really sure what's happening.

Also, I found [this tutorial](http://www.ffnn.nl/pages/articles/apple-mac-os-x/vectorizing-with-vdsp-and-veclib.php) pretty helpful.
this is a great [forum post](http://forum.openframeworks.cc/index.php?topic=10560.0) and explanation of doing [fft with accelreate](http://pkmital.com/home/2011/04/14/real-fftifft-with-the-accelerate-framework/)
