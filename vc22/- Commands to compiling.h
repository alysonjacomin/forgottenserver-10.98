/** FOR WINDOWS **/

git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.bat
./vcpkg.exe integrate install

./vcpkg install --triplet x64-windows boost-asio boost-iostreams boost-system boost-lockfree boost-locale boost-beast boost-json boost-variant luajit libmariadb pugixml openssl fmt