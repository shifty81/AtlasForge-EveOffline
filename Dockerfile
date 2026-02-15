# EVE OFFLINE - Dedicated Server Dockerfile
# Multi-stage build for minimal runtime image

# --- Build stage ---
FROM ubuntu:22.04 AS builder

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /build

# Copy engine and server source, plus data
COPY engine/ engine/
COPY cpp_server/ cpp_server/
COPY data/ data/
COPY CMakeLists.txt CMakeLists.txt

# Build engine and server via root CMake
RUN mkdir -p build \
    && cd build \
    && cmake .. \
        -DCMAKE_BUILD_TYPE=Release \
        -DBUILD_ATLAS_ENGINE=ON \
        -DBUILD_ATLAS_EDITOR=OFF \
        -DBUILD_ATLAS_RUNTIME=OFF \
        -DBUILD_ATLAS_TESTS=OFF \
        -DBUILD_CLIENT=OFF \
        -DBUILD_SERVER=ON \
        -DUSE_STEAM_SDK=OFF \
    && cmake --build . --config Release -j$(nproc)

# --- Runtime stage ---
FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    libstdc++6 \
    && rm -rf /var/lib/apt/lists/*

RUN useradd -m -s /bin/bash eveserver

WORKDIR /opt/eveoffline

# Copy built server binary and config
COPY --from=builder /build/build/cpp_server/bin/eve_dedicated_server .
COPY --from=builder /build/build/cpp_server/bin/config/ config/
COPY data/ data/

RUN chown -R eveserver:eveserver /opt/eveoffline

USER eveserver

EXPOSE 8765

ENTRYPOINT ["./eve_dedicated_server"]
