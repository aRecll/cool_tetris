
FROM ubuntu:24.04 AS build

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    qt6-base-dev \
    qt6-httpserver-dev \
    qt6-websockets-dev \
    libqt6sql6-psql \
    libhiredis-dev \
    libssl-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

RUN mkdir build && cd build && \
    cmake .. && \
    make -j$(nproc)


FROM ubuntu:24.04

RUN apt-get update && apt-get install -y \
    libqt6core6 \
    libqt6network6 \
    libqt6sql6 \
    libqt6sql6-psql \
    libqt6httpserver6 \
    libhiredis1.1.0 \
    libssl3 \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY --from=build /app/build/TetrisServer .

EXPOSE 8443

CMD ["./TetrisServer"]