# Multi-stage build for mscope RPi
FROM --platform=linux/arm64 debian:bookworm-slim as builder

# Install build dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    pkg-config \
    libglfw3-dev \
    libgles2-mesa-dev \
    libegl1-mesa-dev \
    libglm-dev \
    libstb-dev \
    git \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /build

# Copy source code
COPY . .

# Create build directory
RUN mkdir -p build-raspberry-pi

# Build the application
RUN cd build-raspberry-pi && \
    cmake .. && \
    make -j$(nproc)

# Runtime stage
FROM --platform=linux/arm64 debian:bookworm-slim

# Install runtime dependencies
RUN apt-get update && apt-get install -y \
    libglfw3 \
    libgles2-mesa \
    libegl1-mesa \
    libglm \
    libstb \
    && rm -rf /var/lib/apt/lists/*

# Create application directory
RUN mkdir -p /usr/local/bin/mscope

# Copy built binary and assets
COPY --from=builder /build/build-raspberry-pi/mscope /usr/local/bin/mscope/
COPY --from=builder /build/fonts /usr/local/bin/mscope/
COPY --from=builder /build/shader/*.shader /usr/local/bin/mscope/shader/

# Make binary executable
RUN chmod +x /usr/local/bin/mscope/mscope

# Set working directory
WORKDIR /usr/local/bin/mscope

# Default command
CMD ["./mscope"] 