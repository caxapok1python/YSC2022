#!/bin/sh
sudo apt-get purge wolfram-engine
sudo apt-get purge libreoffice*
sudo apt-get clean
sudo apt-get autoremove

sudo apt-get -y update && sudo apt-get -y upgrade
sudo apt-get install -y build-essential cmake pkg-config

sudo apt-get install -y libjpeg-dev libtiff5-dev libjasper-dev libpng-dev
sudo apt-get install -y libavcodec-dev libavformat-dev libswscale-dev libv4l-dev
sudo apt-get install -y libxvidcore-dev libx264-dev

sudo apt-get install -y libfontconfig1-dev libcairo2-dev
sudo apt-get install -y libgdk-pixbuf2.0-dev libpango1.0-dev
sudo apt-get install -y libgtk2.0-dev libgtk-3-dev

sudo apt-get install -y libatlas-base-dev gfortran

sudo apt-get install -y libhdf5-dev libhdf5-serial-dev libhdf5-103
sudo apt-get install -y libqtgui4 libqtwebkit4 libqt4-test python3-pyqt5

sudo apt-get install -y python3-dev
wget https://bootstrap.pypa.io/get-pip.py
sudo python3 get-pip.py
sudo rm -rf ~/.cache/pip

pip3 install opencv-contrib-python==4.1.0.25
sudo echo "CONF_SWAPSIZE=2048" >> /etc/dphys-swapfile


sudo /etc/init.d/dphys-swapfile stop
sudo /etc/init.d/dphys-swapfile start

pip3 install numpy

python3 -c "import cv2; print(cv2.__version__)"

