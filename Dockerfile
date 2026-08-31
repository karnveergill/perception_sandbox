FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

ARG USERNAME=karnveer
ARG USER_UID=1000
ARG USER_GID=1000


# Development packages
RUN apt update && apt install -y \
    build-essential \
    cmake \
    ninja-build \
    git \
    openssh-client \
    gdb \
    clang \
    clangd \
    clang-format \
    clang-tidy \
    cppcheck \
    valgrind \
    python3 \
    python3-pip \
    python3-numpy \
    python3-matplotlib \
    pkg-config \
    libsdl2-dev \
    vim \
    nano \
    sudo \
    bash-completion \
    && rm -rf /var/lib/apt/lists/*

# Create developer user
RUN groupadd --gid ${USER_GID} ${USERNAME} \
    && useradd \
        --uid ${USER_UID} \
        --gid ${USER_GID} \
        --create-home \
        --shell /bin/bash \
        ${USERNAME} \
    && echo "${USERNAME} ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers


# Copy shell configuration
COPY docker/bashrc /home/${USERNAME}/.bashrc
RUN chown ${USERNAME}:${USERNAME} /home/${USERNAME}/.bashrc

# Set symlink to working directory
USER ${USERNAME}
WORKDIR /home/${USERNAME}/Development/project

# Launch bash shell 
CMD ["/bin/bash"]