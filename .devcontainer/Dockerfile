FROM debian:bullseye-slim

# Install necessary dependencies
RUN apt-get update && \
    apt-get install -y \ 
    curl \ 
    build-essential \ 
    wget \
    unzip \
    libxrender1 \
    libxcb-render0 \
    libxcb-render-util0 \
    libxcb-shape0 \
    libxcb-randr0 \
    libxcb-xfixes0 \
    libxcb-sync1 \
    libxcb-shm0 \
    libxcb-icccm4 \
    libxcb-keysyms1 \
    libxcb-image0 \
    libxkbcommon0 \
    libxkbcommon-x11-0 \
    libxext6 \
    libx11-xcb1 \
    libsm6 \
    libice6 \
    libglib2.0-0 \
    udev \
    gdb \
    libncursesw5 \
    zlib1g-dev \
    libffi-dev \
    git \
    cmake \
    clang-format \
    clang-tidy

## Python
# download 
RUN wget https://www.python.org/ftp/python/3.8.18/Python-3.8.18.tgz \
    && tar -xf Python-3.8.18.tgz \
    && rm Python-3.8.18.tgz

# install and creat symbolic link
RUN cd /Python-3.8.18 \
    && ./configure --enable-optimizations --with-lto --enable-shared --prefix=/usr/local \
    && make -j 4 \
    && make altinstall \
    && ln -s /usr/local/lib/libpython3.8.so.1.0 /usr/lib/x86_64-linux-gnu

## ARM toolchain
# download and install
RUN ARM_TOOLCHAIN_VERSION="13.2.rel1" && \
    curl -Lo gcc-arm-none-eabi.tar.xz "https://developer.arm.com/-/media/Files/downloads/gnu/${ARM_TOOLCHAIN_VERSION}/binrel/arm-gnu-toolchain-${ARM_TOOLCHAIN_VERSION}-x86_64-arm-none-eabi.tar.xz" && \
    mkdir /opt/gcc-arm-none-eabi && \
    tar xf gcc-arm-none-eabi.tar.xz --strip-components=1 -C /opt/gcc-arm-none-eabi

# Add ARM toolchain to PATH
ENV PATH=$PATH:/opt/gcc-arm-none-eabi/bin

## Jlink tools
# download and install
RUN wget --post-data 'accept_license_agreement=accepted&non_emb_ctr=confirmed&submit=Download+software' https://www.segger.com/downloads/jlink/JLink_Linux_x86_64.deb \
    && dpkg --unpack JLink_Linux_x86_64.deb \
    && rm -f /var/lib/dpkg/info/jlink.postinst \
    && dpkg --configure jlink \
    && apt install -yf

# Add Jlink tools to PATH
ENV PATH="/opt/SEGGER/JLink:${PATH}"

