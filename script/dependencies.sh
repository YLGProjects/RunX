#!/bin/bash

mkdir -p /tmp/ylgeeker/

# install openssl
cd /tmp/ylgeeker
wget https://github.com/openssl/openssl/archive/refs/tags/openssl-3.2.1.tar.gz --no-check-certificate
tar -zvxf openssl-3.2.1.tar.gz
cd openssl-openssl-3.2.1
./config --prefix=/usr/local/openssl-3.2.1
make depend
make -j$(nproc)
make install

rm -rf /tmp/ylgeeker/*

# install boost
cd /tmp/ylgeeker
wget https://github.com/boostorg/boost/releases/download/boost-1.87.0/boost-1.87.0-b2-nodocs.tar.gz --no-check-certificate
tar -zvxf boost-1.87.0-b2-nodocs.tar.gz
cd boost-1.87.0

./bootstrap.sh --with-libraries=all --prefix=/usr/local/boost-1.87.0
./b2 --address-model=64 --link=static --runtime-link=static --variant=release --threading=multi
./b2 install

rm -rf /tmp/ylgeeker/*

# install libevent
cd /tmp/ylgeeker
wget https://github.com/libevent/libevent/archive/refs/tags/release-2.1.12-stable.tar.gz --no-check-certificate
tar -zvxf release-2.1.12-stable.tar.gz
cd libevent-release-2.1.12-stable
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local/libevent-2.1.12
make -j$(nproc) && make install
rm -rf /tmp/ylgeeker/*

# install hiredis
cd /tmp/ylgeeker
wget https://github.com/redis/hiredis/archive/refs/tags/v1.2.0.tar.gz --no-check-certificate
tar -zvxf v1.2.0.tar.gz
cd hiredis-1.2.0
export PREFIX=/usr/local/hiredis-1.2.0
make  -j$(nproc)
make install
rm -rf /tmp/ylgeeker/*

# install redis-plus-plus
cd /tmp/ylgeeker
wget https://github.com/sewenew/redis-plus-plus/archive/refs/tags/1.3.13.tar.gz --no-check-certificate
tar -zvxf 1.3.13.tar.gz
cd redis-plus-plus-1.3.13
mkdir build
cd build
cmake .. -DCMAKE_PREFIX_PATH=/usr/local/hiredis-1.2.0  -DCMAKE_INSTALL_PREFIX=/usr/local/redis-plus-plus-1.3.13 -DREDIS_PLUS_PLUS_BUILD_TEST=OFF
make -j$(nproc)
make install
rm -rf /tmp/ylgeeker/*

# install concurentqueue
cd /tmp/ylgeeker
wget https://github.com/cameron314/concurrentqueue/archive/refs/tags/v1.0.4.tar.gz --no-check-certificate
tar -zvxf v1.0.4.tar.gz
cd concurrentqueue-1.0.4
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local/concurrentqueue-1.0.4
cmake --build . --target install
rm -rf /tmp/ylgeeker/*

# install spdlog
cd /tmp/ylgeeker
wget https://github.com/gabime/spdlog/archive/refs/tags/v1.13.0.tar.gz --no-check-certificate
tar -zvxf v1.13.0.tar.gz
cd spdlog-1.13.0 && mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local/spdlog-1.13.0
make -j$(nproc)
make install
rm -rf /tmp/ylgeeker/*

# install Catch2
cd /tmp/ylgeeker
wget https://github.com/catchorg/Catch2/archive/refs/tags/v3.5.3.tar.gz --no-check-certificate
tar -zvxf v3.5.3.tar.gz
cd Catch2-3.5.3
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local/catch2-3.5.3
make -j$(nproc)
make install
rm -rf /tmp/ylgeeker/*

# install grpc(dependenced by etcd-cpp-apiv3)
apt-get install libcpprest-dev
apt-get install libgrpc-dev \
        libgrpc++-dev \
        libprotobuf-dev \
        protobuf-compiler-grpc

cd /tmp/ylgeeker
git clone --recurse-submodules -b v1.62.0 --depth 1 --shallow-submodules https://github.com/grpc/grpc
cd grpc
mkdir -p cmake/build
pushd cmake/build
cmake -DCMAKE_INSTALL_PREFIX=/usr/local/grpc-1.62.0 -DgRPC_INSTALL=ON \
      -DgRPC_BUILD_TESTS=OFF \
      ../..

make -j$(nproc)
make install
popd
rm -rf /tmp/ylgeeker/*

# install etcd-cpp-apiv3
cd /tmp/ylgeeker
git clone https://github.com/etcd-cpp-apiv3/etcd-cpp-apiv3.git
cd etcd-cpp-apiv3
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local/etcd-cppapiv3 -DBUILD_SHARED_LIBS=OFF
make -j$(nproc) && make install

rm -rf /tmp/ylgeeker/*

# install mongo-cxx-driver
cd /tmp/ylgeeker
wget https://github.com/mongodb/mongo-cxx-driver/releases/download/r3.10.1/mongo-cxx-driver-r3.10.1.tar.gz
tar -xzf mongo-cxx-driver-r3.10.1.tar.gz
cd mongo-cxx-driver-r3.10.1
mkdir build
cd build
cmake  -DCMAKE_INSTALL_PREFIX=/usr/local/mongo-cxx-driver-r3.10.1 -DCMAKE_BUILD_TYPE=Release \
       -DBUILD_SHARED_LIBS=OFF \
       -DBUILD_SHARED_AND_STATIC_LIBS=OFF \
       -DMONGOCXX_ENABLE_SSL=OFF \
       -DBSONCXX_POLY_USE_STD=OFF \
       -DENABLE_SSL=OFF \
       -DMONGOCXX_OVERRIDE_DEFAULT_INSTALL_PREFIX=OFF ..

make -j$(nproc)
make install

# install rapidjson
cd /tmp/ylgeeker
git clone https://github.com/Tencent/rapidjson.git
cd rapidjson
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local/rapidjson -DCMAKE_INSTALL_DIR=/usr/local/rapidjson/cmake \
    -DDOC_INSTALL_DIR=/usr/local/rapidjson/doc -DINCLUDE_INSTALL_DIR=/usr/local/rapidjson/include \
    -DLIB_INSTALL_DIR=/usr/local/rapidjson/lib -DRAPIDJSON_HAS_STDSTRING=ON

make -j$(nproc)
make install
rm -rf /tmp/ylgeeker/*

# install yaml
cd /tmp/ylgeeker
wget https://github.com/jbeder/yaml-cpp/archive/refs/tags/0.8.0.tar.gz --no-check-certificate
tar -zxvf 0.8.0.tar.gz
cd yaml-cpp-0.8.0
mkdir -p build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local/yaml-cpp-0.8.0
make
make install
rm -rf /tmp/ylgeeker/*

# install curl
cd /tmp/ylgeeker
wget https://github.com/curl/curl/releases/download/curl-8_11_1/curl-8.11.1.tar.gz --no-check-certificate
tar -zxvf curl-8.11.1.tar.gz
cd curl-8.11.1
./configure --prefix=/usr/local/curl-8.11.1 --with-openssl --without-libpsl --enable-versioned-symbols
make -j$(nproc)
make install

rm -rf /tmp/ylgeeker/*

# install prometheus-cpp
cd /tmp/ylgeeker
wget https://github.com/jupp0r/prometheus-cpp/releases/download/v1.2.4/prometheus-cpp-with-submodules.tar.gz --no-check-certificate
tar -zvxf prometheus-cpp-with-submodules.tar.gz
cd prometheus-cpp-with-submodules
mkdir build
cd build
cmake -DBUILD_SHARED_LIBS=OFF -DENABLE_PUSH=OFF -DENABLE_COMPRESSION=OFF -DENABLE_TESTING=OFF \
    -DCMAKE_INSTALL_PREFIX=/usr/local/prometheus-cpp-1.2.4 ..

make -j$(nproc)
make install

rm -rf /tmp/ylgeeker/*
