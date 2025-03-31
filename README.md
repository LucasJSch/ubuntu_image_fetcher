# Build the Docker image
docker build -t ubuntu_fetcher .

# Run the container
docker run --rm -it -v "$PWD":/app ubuntu_fetcher
