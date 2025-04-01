# Build the Docker image
`docker build -t ubuntu_image_fetcher .`

# Run the container
`docker run --rm -it -v "$PWD":/app ubuntu_image_fetcher`

# Build the project inside the docker container
```bash
mkdir build && cd build
cmake ..
make
./ubuntu_image_fetcher --list
```

# Available commands
- `--list`: List all available Ubuntu images.
- `--lts`: Prints latest Ubuntu LTS image.
- `--sha256 <image_name>`: Prints the SHA256 checksum of the latest version of the specified image.