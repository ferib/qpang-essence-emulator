# Essence-emulator

## Instructions
- Clone this repository
- Open any terminal in the project's root directory (besides git bash)
- Run the following commands:
 1. ``` mkdir build ```
 2. ``` cd build ```
 3. ``` cmake .. ```, If your boost_root is not set in cmake, use the following command: ```cmake -DBOOST_ROOT=path .. ```
- Edit the `database.hpp` source definitions to your own MySQL credentials.
 

## Requirements

- https://github.com/DeluzeDEV/essence-site installed and running

- vcpkg (install ```curl``` , ```curlpp``` and ```spdlog```)
- CMake (Up-to-date version)
- Boost 1.68.0 (tested)
- MySQL server (if database is hosted locally)

## Additional information

### Game version
If you want to host this server for another game version, change the game_version value in the 'settings' table in the database, otherwise it won't work.
 
## About
This is a server emulator for the game QPang. This emulator is being built around the 2012 version of this game.
