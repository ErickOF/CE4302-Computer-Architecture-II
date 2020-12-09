# Install dependencies
sudo apt-get install cmake pkg-config python ocl-icd-dev libegl1-mesa-dev
sudo apt-get install ocl-icd-opencl-dev libdrm-dev libxfixes-dev
sudo apt-get install libxext-dev llvm-3.9-dev clang-3.9 libclang-3.9-dev
sudo apt-get install libtinfo-dev libedit-dev zlib1g-dev

# Clone OpenCL from Beignet
git clone https://anongit.freedesktop.org/git/beignet.git

# Install
cd beignet
mkdir -p build && cd build
cmake ../
make -j8
make utest -j8
sudo make install

# Check compatibility
#cd utest
#. setenv.sh
#./utest_run

# Test installation
#gcc -o devices devices.c -lOpenCL
#./devices

