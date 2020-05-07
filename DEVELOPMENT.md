# Development

## 5/6/2020
Last Day!
- Switching to Numbeo climate index instead of temperature for weather data
    - centralizes all API-related requests into 1 call/city
- Refining algorithm to not give the same cities over and over again by lowering
the weight of cost of living 
- Rearranged question order to reflect change in weather data
- All public functions in src are tested successfully
    - Issues with small populations fixed
- **Project is fully functional!**

## 5/5/2020
- HTTPRequest library reverted to functional version
- Started writing tests
- Numbeo API data integrated successfully into engine
- Engine returns cities with only some errors
    - Works better for larger population cities
    - Not all parameter data exists for smaller towns
- All parameters except weather accounted for in engine
- Challenge: weather API maxes out at 500 calls/day
    - Weather integration may need to be manual
    - Will start with most populous cities
    - Only considered for algorithm if available
    
## 5/4/2020
- Climate API changed to World Weather Online
- Added population question, modified question directions
- Passed info from user to engine
- HTTP Requests stopped working (doesn't work in any CLion project, but API
works anywhere else)
    - May have to get all data statically in Java and store to be accessed via
    JSON

Working on:
- Making engine funcitonal
- Actually starting to make API calls
- Testing


## 5/3/2020
- Acquired academic license for Numbeo API
- Json serialization/deserialization functional
- Changed population data from API to local static dataset
- Integrated population dataset as vector of cities
- Parsing JSON and beginning classification

## 4/29/2020
- Clicking and typing flow to answer questions

Working on:
- Ending screen
- Getting data and producing a response

## 4/28/2020 
- Nlohmann json library integrated

APIs selected:
- Climate: Azavea
- Population/City Names: GeoDB
- Crime/CoL/Pollution/Traffic/QoL: Numbeo 


## 4/27/2020 
Next Objectives:
- Text/questions display correctly and look nice
- Flow of program executes (without data right now)
- Finalize APIs and get authorization keys

## 4/26/2020
- Displayed text and rectangles as test
- Using PrintText helper method from snake MP

## 4/21/2020
- Added HTTPRequest and cpp-httplib external libraries
- Successfully ran HTTP request to test API endpoint
- Added and removed button CinderBlock
---
