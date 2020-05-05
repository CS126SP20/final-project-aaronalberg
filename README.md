# Home Finder - CS 126 Final Project

[![license](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![docs](https://img.shields.io/badge/docs-yes-brightgreen)](docs/README.md)

**Aaron Alberg** - [`aalberg2@illinois.edu`](mailto:aalberg2@illinois.edu)
---

## Purpose
HomeFinder was built to provide users a tool for finding their next home based 
on their preferences for population, traffic, pollution, cost of living, 
healthcare, and weather. It uses a simple weighting of each parameter to 
provide the best possible match.

## Getting Started
HomeFinder is a CMake applicaiton built with the Cinder framework. Download
 Cinder [here](https://libcinder.org/download).
 It also uses the [nlohmann json](https://github.com/nlohmann/json) and the 
 [HTTPRequest](https://github.com/elnormous/HTTPRequest) libraries.

Setting up Cinder + Home Finder in CLion
1. Download Cinder (v0.9.2) for your platform. Extract the downloaded item into 
a folder. We’ll call this folder ~/Cinder throughout the instructions
2. Open the ~/Cinder folder in CLion and click the green build button. This will
build libcinder. You only need to do this once per machine. 
This build might take a while.
3. Create a directory, say 'cinder-projects' in ~/Cinder. Clone the 
**Home Finder** project repo into this folder.
4. Open the Home Finder project in CLion, set the target to cinder-myapp 
and click the run button. Alternatively, you can run the application from the
command line.

## Using HomeFinder
Once you've launched HomeFinder from your IDE or the command line, you can begin 
finding your next hometown. Simply use your keyboard to 
enter any values that are asked for and click the next button when you are 
satisfied with your response.
Make sure you have an internet connection before starting.

#### Valid Responses

Depending on the question, there may be a different set of valid input values.
All questions can only be answered using keyboard digits 0 - 9, also known as 
the ASCII characters with codes 48 - 57, inclusive. If your response is not 
valid (blank, out of bounds, etc.) it will be erased or an error message will
appear.

#### Erasing your response

If you accidentally mistyped or want to enter a different value, press any
non-digit (0 - 9) key and your response will be cleared.

## Getting a Result
After answering all the questions, HomeFinder will use your responses to find 
a city that matches as close as possible to your preferences. The city that you
are provided with should match at least somewhat closely to most of 
your preferences. Unfortunately, there aren't enough cities in the world to
match everyone exactly.

## License
This project is under the MIT license. Please refer to the LICENSE file for
 detailed information.

## Credits
Thanks to:
- CS 126 Piazza
- Stack Overflow
