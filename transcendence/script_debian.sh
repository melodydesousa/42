#!/bin/bash
sudo apt update && \
sudo apt upgrade -y && \
sudo apt install -y curl fish make usermode && \
sudo curl -o docker-desktop.deb "https://desktop.docker.com/linux/main/amd64/docker-desktop-4.21.1-amd64.deb?utm_source=docker&utm_medium=webreferral&utm_campaign=docs-driven-download-linux-amd64"
sudo apt install ./docker-desktop.deb
sudo usermod -aG docker $USER
sudo systemctl --user start docker-desktop
curl -sL https://deb.nodesource.com/setup_18.x | sudo -E bash - && \
curl -sL https://dl.yarnpkg.com/debian/pubkey.gpg | gpg --dearmor | sudo tee /usr/share/keyrings/yarnkey.gpg >/dev/null
echo "deb [signed-by=/usr/share/keyrings/yarnkey.gpg] https://dl.yarnpkg.com/debian stable main" | sudo tee /etc/apt/sources.list.d/yarn.list
sudo apt-get update && sudo apt-get install yarn
sudo apt update && \
sudo apt upgrade -y && \
sudo apt install -y nodejs && \
node -v && npm -v && \
sudo npm i -g @nestjs/cli 
# sudo apt install postgresql postgresql-contrib && \
# sudo systemctl start postgresql.service
# Add Insomnia to sources
echo "deb [trusted=yes arch=amd64] https://download.konghq.com/insomnia-ubuntu/ default all" \
    | sudo tee -a /etc/apt/sources.list.d/insomnia.list
# Refresh repository sources and install Insomnia
sudo apt update
sudo apt install -y insomnia git htop gcc lldb valgrind terminator
