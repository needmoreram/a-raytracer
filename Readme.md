# A Ray Tracer

Following the tutorial by Peter Shirley [here](https://www.realtimerendering.com/raytracing/Ray%20Tracing%20in%20a%20Weekend.pdf)

Also following the write-up by Johann Muszynski [here](https://nelari.us/post/raytracer_with_rust_and_zig/)

## Requirements

Needs `ninja` and `meson` executables.
Also needs `eigen3` library.

## Building

```
cd a-raytracer/
meson build
cd build/
ninja
```

## Running

Each executable outputs an image in [PPM format](https://en.wikipedia.org/wiki/Netpbm#PPM_example). Simply pipe output to a file, say `output.ppm`, and view it with your favourite image viewer.
