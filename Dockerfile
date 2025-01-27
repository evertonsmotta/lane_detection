# Use uma imagem base com o Ubuntu
FROM ubuntu:20.04

# Evitar perguntas interativas durante a instalação
ARG DEBIAN_FRONTEND=noninteractive

# Instalar dependências necessárias
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    pkg-config \
    libopencv-dev \
    libpthread-stubs0-dev \
    git \
    wget \
    unzip \
    && apt-get clean

# Instalar o OpenCV 4 (caso não esteja disponível diretamente no repositório)
RUN wget -qO - https://github.com/opencv/opencv/archive/4.x.zip -O /opencv-4.x.zip \
    && unzip /opencv-4.x.zip -d /opencv \
    && cd /opencv/opencv-4.x \
    && mkdir build && cd build \
    && cmake .. && make -j$(nproc) && make install \
    && ldconfig

# Definir o diretório de trabalho
WORKDIR /app

# Copiar todos os arquivos do projeto para o contêiner
COPY . .

# Compilar o código C++ usando o g++
RUN g++ lane_detection.cpp -o lane_detection `pkg-config --cflags --libs opencv4`

# Comando para rodar a aplicação
CMD ["./lane_detection"]
