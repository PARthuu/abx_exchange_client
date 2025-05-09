# ABX Client

A C++ client for interacting with the ABX mock exchange server.

## Build

```sh
mkdir build
cd build
cmake ..
make
```

## Run

```sh
./abx_client <hostname>
```

Example:

```sh
./abx_client 127.0.0.1
```

Output will be written to `data/output.json`
