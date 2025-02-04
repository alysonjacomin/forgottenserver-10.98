git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.bat
./vcpkg.exe integrate install

./vcpkg install --triplet x64-windows boost-asio boost-iostreams boost-system boost-filesystem boost-variant boost-lockfree luajit libmariadb pugixml cryptopp fmt