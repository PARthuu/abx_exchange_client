# ABX Client

A C++ client for interacting with the ABX mock exchange server.

## Build

```sh
cmake . -B build
cmake --build build
```
Client will be in `build` directory. 

## Run

```sh
./abx_client <hostname>
```

Example:

```sh
./abx_client 127.0.0.1
./abx_client localhost
```

Output will be written to `packages.json`
