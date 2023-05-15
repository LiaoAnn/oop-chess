# websocket++

This file provides an overview of the necessary steps for setting up the environment to compile WebSock++ under normal circumstances.

## Recommended IDE Setup

VS2022 (v143) is the only version that has been tested and confirmed to be compatible with the latest versions of Boost (1.82.0) and WebSocket++ (0.8.2). Please make sure to use the correct versions accordingly.

## Installation

#### Boost

1. You can download the source code from [Boost](https://www.boost.org/) and compile it yourself, but it is recommended to download a pre-compiled version from [sourceforge](https://sourceforge.net/projects/boost/files/boost-binaries/) for easier installation.
2. After downloading, install Boost to a specified location based on your needs.
3. Run bootstrap.bat to generate b2.exe, and then run b2.exe.
4. The stage folder will be generated in the directory, which is the directory that the linker needs.

#### WebSocket++

1. Download the source code files from the [WebSocket++](https://docs.websocketpp.org/) official website or [GitHub](https://github.com/zaphoyd/websocketpp/).
2. Unzip the files to the specified location.

#### IDE setup

1. Set the "Additional Include Directories" to include the Boost and WebSocket root directories.

2. Add the boost\stage\lib (sometimes libs) directory to "Additional Library Directories."

