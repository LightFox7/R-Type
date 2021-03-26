mkdir -p build && cd build && conan install .. && cmake .. && make && cd - && mv build/lib/*.so ./monsterLibs/ && mv build/bin/r-type_client . && mv build/bin/r-type_server .
