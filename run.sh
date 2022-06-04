# Initial cmake
cmake -Bcmake-build-debug -H.

# Run
cd cmake-build-debug/
make
./my_tanks_in_labirint

# How to use protoc
# protoc -I=inc/ --cpp_out=dest/ inc/addressbook.proto

# Compile protoc
# g++ dest/addressbook.pb.cc server.cpp -std=c++17 -pthread -lprotobuf -lpthread -o server