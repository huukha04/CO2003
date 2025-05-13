g++ -std=c++17 -pthread  -Iinclude -Iinclude/ann -Iinclude/tensor -Iinclude/sformat -Idemo -Isrc -c   src/program.cpp -o obj/program.o
mkdir -p obj/tensor/
g++ -std=c++17 -pthread  -Iinclude -Iinclude/ann -Iinclude/tensor -Iinclude/sformat -Idemo -Isrc -c   src/tensor/xtensor_lib.cpp -o obj/tensor/xtensor_lib.o
mkdir -p obj/ann/
g++ -std=c++17 -pthread  -Iinclude -Iinclude/ann -Iinclude/tensor -Iinclude/sformat -Idemo -Isrc -c   src/ann/functions.cpp -o obj/ann/functions.o
mkdir -p obj/ann/dataset/
g++ -std=c++17 -pthread  -Iinclude -Iinclude/ann -Iinclude/tensor -Iinclude/sformat -Idemo -Isrc -c   src/ann/dataset/DSFactory.cpp -o obj/ann/dataset/DSFactory.o
mkdir -p obj/ann/config/
g++ -std=c++17 -pthread  -Iinclude -Iinclude/ann -Iinclude/tensor -Iinclude/sformat -Idemo -Isrc -c   src/ann/config/Config.cpp -o obj/ann/config/Config.o
mkdir -p obj/ann/layer/
g++ -std=c++17 -pthread  -Iinclude -Iinclude/ann -Iinclude/tensor -Iinclude/sformat -Idemo -Isrc -c   src/ann/layer/Layer.cpp -o obj/ann/layer/Layer.o
mkdir -p obj/ann/layer/
g++ -std=c++17 -pthread  -Iinclude -Iinclude/ann -Iinclude/tensor -Iinclude/sformat -Idemo -Isrc -c   src/ann/layer/FCLayer.cpp -o obj/ann/layer/FCLayer.o
mkdir -p obj/ann/layer/
g++ -std=c++17 -pthread  -Iinclude -Iinclude/ann -Iinclude/tensor -Iinclude/sformat -Idemo -Isrc -c   src/ann/layer/ReLU.cpp -o obj/ann/layer/ReLU.o
mkdir -p obj/ann/layer/
g++ -std=c++17 -pthread  -Iinclude -Iinclude/ann -Iinclude/tensor -Iinclude/sformat -Idemo -Isrc -c   src/ann/layer/Sigmoid.cpp -o obj/ann/layer/Sigmoid.o
mkdir -p obj/ann/layer/
g++ -std=c++17 -pthread  -Iinclude -Iinclude/ann -Iinclude/tensor -Iinclude/sformat -Idemo -Isrc -c   src/ann/layer/Softmax.cpp -o obj/ann/layer/Softmax.o
mkdir -p obj/ann/layer/
g++ -std=c++17 -pthread  -Iinclude -Iinclude/ann -Iinclude/tensor -Iinclude/sformat -Idemo -Isrc -c   src/ann/layer/Tanh.cpp -o obj/ann/layer/Tanh.o
mkdir -p obj/ann/loss/
g++ -std=c++17 -pthread  -Iinclude -Iinclude/ann -Iinclude/tensor -Iinclude/sformat -Idemo -Isrc -c   src/ann/loss/CrossEntropy.cpp -o obj/ann/loss/CrossEntropy.o
mkdir -p obj/ann/loss/
g++ -std=c++17 -pthread  -Iinclude -Iinclude/ann -Iinclude/tensor -Iinclude/sformat -Idemo -Isrc -c   src/ann/loss/LossLayer.cpp -o obj/ann/loss/LossLayer.o
mkdir -p obj/ann/metrics/
g++ -std=c++17 -pthread  -Iinclude -Iinclude/ann -Iinclude/tensor -Iinclude/sformat -Idemo -Isrc -c   src/ann/metrics/ClassMetrics.cpp -o obj/ann/metrics/ClassMetrics.o
mkdir -p obj/ann/metrics/
g++ -std=c++17 -pthread  -Iinclude -Iinclude/ann -Iinclude/tensor -Iinclude/sformat -Idemo -Isrc -c   src/ann/metrics/IMetrics.cpp -o obj/ann/metrics/IMetrics.o
mkdir -p obj/ann/model/
g++ -std=c++17 -pthread  -Iinclude -Iinclude/ann -Iinclude/tensor -Iinclude/sformat -Idemo -Isrc -c   src/ann/model/IModel.cpp -o obj/ann/model/IModel.o
mkdir -p obj/ann/model/
g++ -std=c++17 -pthread  -Iinclude -Iinclude/ann -Iinclude/tensor -Iinclude/sformat -Idemo -Isrc -c   src/ann/model/MLPClassifier.cpp -o obj/ann/model/MLPClassifier.o
mkdir -p obj/ann/optim/
g++ -std=c++17 -pthread  -Iinclude -Iinclude/ann -Iinclude/tensor -Iinclude/sformat -Idemo -Isrc -c   src/ann/optim/Adagrad.cpp -o obj/ann/optim/Adagrad.o
mkdir -p obj/ann/optim/
g++ -std=c++17 -pthread  -Iinclude -Iinclude/ann -Iinclude/tensor -Iinclude/sformat -Idemo -Isrc -c   src/ann/optim/Adam.cpp -o obj/ann/optim/Adam.o
mkdir -p obj/ann/optim/
g++ -std=c++17 -pthread  -Iinclude -Iinclude/ann -Iinclude/tensor -Iinclude/sformat -Idemo -Isrc -c   src/ann/optim/AdamParamGroup.cpp -o obj/ann/optim/AdamParamGroup.o
mkdir -p obj/ann/optim/
g++ -std=c++17 -pthread  -Iinclude -Iinclude/ann -Iinclude/tensor -Iinclude/sformat -Idemo -Isrc -c   src/ann/optim/AdaParamGroup.cpp -o obj/ann/optim/AdaParamGroup.o
mkdir -p obj/ann/optim/
g++ -std=c++17 -pthread  -Iinclude -Iinclude/ann -Iinclude/tensor -Iinclude/sformat -Idemo -Isrc -c   src/ann/optim/Optimizer.cpp -o obj/ann/optim/Optimizer.o
mkdir -p obj/ann/optim/
g++ -std=c++17 -pthread  -Iinclude -Iinclude/ann -Iinclude/tensor -Iinclude/sformat -Idemo -Isrc -c   src/ann/optim/SGD.cpp -o obj/ann/optim/SGD.o
mkdir -p obj/ann/optim/
g++ -std=c++17 -pthread  -Iinclude -Iinclude/ann -Iinclude/tensor -Iinclude/sformat -Idemo -Isrc -c   src/ann/optim/SGDParamGroup.cpp -o obj/ann/optim/SGDParamGroup.o

g++ -std=c++17 -pthread  -Iinclude -Iinclude/ann -Iinclude/tensor -Iinclude/sformat -Idemo -Isrc   obj/program.o  obj/tensor/xtensor_lib.o  obj/ann/functions.o  obj/ann/dataset/DSFactory.o  obj/ann/config/Config.o  obj/ann/layer/Layer.o  obj/ann/layer/FCLayer.o  obj/ann/layer/ReLU.o  obj/ann/layer/Sigmoid.o  obj/ann/layer/Softmax.o  obj/ann/layer/Tanh.o  obj/ann/loss/CrossEntropy.o  obj/ann/loss/LossLayer.o  obj/ann/metrics/ClassMetrics.o  obj/ann/metrics/IMetrics.o  obj/ann/model/IModel.o  obj/ann/model/MLPClassifier.o  obj/ann/optim/Adagrad.o  obj/ann/optim/Adam.o  obj/ann/optim/AdamParamGroup.o  obj/ann/optim/AdaParamGroup.o  obj/ann/optim/Optimizer.o  obj/ann/optim/SGD.o  obj/ann/optim/SGDParamGroup.o -o program -lm -lpthread;./program.exe | Out-File -FilePath output.txt