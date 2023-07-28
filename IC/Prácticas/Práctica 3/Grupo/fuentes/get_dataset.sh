
mkdir build
cd build

# Create train folder
mkdir train
cd train
# Get train data
wget http://yann.lecun.com/exdb/mnist/train-images-idx3-ubyte.gz
gzip -d train-images-idx3-ubyte.gz

wget http://yann.lecun.com/exdb/mnist/train-labels-idx1-ubyte.gz
gzip -d train-labels-idx1-ubyte.gz

cd ..

# Create test folder
mkdir test
cd test
# Get test data
wget http://yann.lecun.com/exdb/mnist/t10k-images-idx3-ubyte.gz
gzip -d t10k-images-idx3-ubyte.gz

wget http://yann.lecun.com/exdb/mnist/t10k-labels-idx1-ubyte.gz
gzip -d t10k-labels-idx1-ubyte.gz

cd ..

# Create makefile
cmake -S .. -B .
make

