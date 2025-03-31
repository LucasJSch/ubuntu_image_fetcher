FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    curl \
    wget \
    libssl-dev \
    libcurl4-openssl-dev \
    && rm -rf /var/lib/apt/lists/*

# Install JSON
RUN mkdir -p /usr/local/include/nlohmann && \
    wget -qO /usr/local/include/nlohmann/json.hpp https://github.com/nlohmann/json/releases/latest/download/json.hpp

# Install CPR
RUN git clone https://github.com/libcpr/cpr.git /tmp/cpr && \
    cd /tmp/cpr && mkdir build && cd build && \
    cmake .. -DBUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX=/usr/local && \
    make -j$(nproc) && make install && \
    rm -rf /tmp/cpr

WORKDIR /app

CMD ["bash"]