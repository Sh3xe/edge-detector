# Edge Detector

This project can load PGM files and perform an edge detection algorithm based on the minimization of an energy function as described in the "Method" section. It then exports this image in PGM format.
## Build and Run

Run cmake -B build and then use your preferred build system to compile.
## Method

This repository implements the method developed in "Active Contours Without Edges" (DOI: 10.1109/83.902291) by Tony F. Chan, Member, IEEE, and Luminita A. Vese.