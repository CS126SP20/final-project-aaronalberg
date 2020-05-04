# Home Finder - CS 126 Final Project

[![license](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![docs](https://img.shields.io/badge/docs-yes-brightgreen)](docs/README.md)

Read [this document](https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html) to understand the project
layout.

**Author**: Aaron Alberg - [`aalberg2@illinois.edu`](mailto:example@illinois.edu)
---

## Purpose
Home Finder was built to provide users a tool for finding their next home based 
on their preferences for population, traffic, pollution, cost of living, 
healthcare, and weather. It uses a simple weighting of each parameter to 
provide the best possible match.

## Getting Started
Home Finer is a CMake applicaiton built with the Cinder framework. Download
 Cinder [here](https://libcinder.org/download).

Setting up Cinder + Home Finder
1. Download Cinder (v0.9.2) for your platform. Extract the downloaded item into 
a folder. We’ll call this folder ~/Cinder throughout the instructions
2. Open the ~/Cinder folder in CLion and click the green build button. This will
 build libcinder. You only need to do this once per machine. This build might take a while.
3. Create a directory, say cinder-projects in ~/Cinder. Clone the 
**Home Finder** project repo into this folder.
4. Open the Home Finder project in CLion, set the target to cinder-myapp 
and click the run button.