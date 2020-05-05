# HomeFinder

**Author: Aaron Alberg**

My final project idea is an application that finds the most ideal place to live 
based on parameters input by the user. I don't think a ton of subject matter 
knowledge on the topic is required except the parameters I want to use to select
the 'ideal' location. I will use the following parameters: population, weather, 
healthcare, crime, cost of living, and pollution. To calculate the ideal city,
I will use a simple weighting system to find a good match.

I will use the nlohmann json library to parse JSON data both from a file and
from API calls. The API calls will be made using the HTTPRequest library. I will
use the World Weather Online API for weather data, and the Numbeo API for all
other calls. To limit the list of cities I am checking against, I will use a 
pre-downloaded static dataset containing roughly 15,000 cities and their data.

The first week will be spent familiarizing myself with Cinder and setting up my
external libraries with CMake. The second week will be spent developing the
frontend/visual aspects of the project. This will consist of screens with
buttons for the user to press and the ability to type responses. The final week
will be spent accessing the data and using it to develop a simple city-picking
algorithm. In the third week I will also work on the README documentation and 
writing test cases.

---