# Nitrokey password example

Small code using libnitrokey API.

## Install libnitrokey

https://github.com/Nitrokey/libnitrokey

```
git clone --recursive https://github.com/Nitrokey/libnitrokey.git
# assuming current dir is ./libnitrokey/
mkdir -p build
cd build
cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr .. 
make -j2
sudo make install
```
