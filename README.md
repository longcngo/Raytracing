# Raytracing

## Intro
A ray tracing program based on Peter Shirley's Ray Tracing in a Weekend series
of books. Remembering the toil in creating a Ray tracer in Java for a
university graphics class, I decided to give this another go by refreshing
my graphics knowledge and trying to build up a project from scratch
(at least as far as using C++).

## Features

- Anti-Aliasing
- Mirror and Glass material
- Motion Blur
- Acceleration Structures (Bounding Volume Hierarchies)
- Basic Global Illumination (Direct Ray Tracing and Path Tracing)
- Texture Generation
- Image Textures
- Triangle Meshes
- Instancing

##Resources
- [Peter Shirly's in a Weekend Series](http://in1weekend.blogspot.com/2016/01/ray-tracing-in-one-weekend.html) for an easy going introduction in coding up a simple ray tracer.
- [Realistic Ray Tracing](https://www.indiebound.org/book/9781568814612) which is basically a more advanced and formal version of the Weekend Series. Also Includes C++ code to follow along.
- [An Efficient and Robust Ray–Box Intersection Algorithm](https://people.csail.mit.edu/amy/papers/box-jgt.pdf) A paper which describes an optimized bounding box intersection.
- [xoroshiro128plus](http://vigna.di.unimi.it/xorshift/xoroshiro128plus.c) source code for the RNG used here.
- [Perlin Noise Explanation](https://flafla2.github.io/2014/08/09/perlinnoise.html) Much more intuative than other resources.
- [Graphics Gems](http://www.realtimerendering.com/resources/GraphicsGems/) For pointers on certain problems like bounding box transformations
