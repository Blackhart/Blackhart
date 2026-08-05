FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
 && apt-get install -y --no-install-recommends \
    ca-certificates \
    python3 \
    python-is-python3 \
    build-essential \
    cmake \
    clang-format \
    git \
    make \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    libopengl-dev \
    libx11-dev \
    libxrandr-dev \
    libxinerama-dev \
    libxcursor-dev \
    libxi-dev \
    libomp-dev \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

USER ubuntu
