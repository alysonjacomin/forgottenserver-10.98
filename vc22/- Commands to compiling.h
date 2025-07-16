/** FOR WINDOWS 10+ **/

cd C:/
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.bat
./vcpkg.exe integrate install

Open Visual Studio Solution

BUILD the project

// ATTENTION: if Visual Studio Solution does not automatically install the LIBs:

/* for x64: */
./vcpkg install --triplet x64-windows boost-asio boost-iostreams boost-locale boost-lockfree boost-system boost-variant luajit libmariadb pugixml openssl fmt

/* for x86: */
./vcpkg install --triplet x86-windows boost-asio boost-iostreams boost-locale boost-lockfree boost-system boost-variant luajit libmariadb pugixml openssl fmt



/** FOR LINUX (Ubuntu 22.04+ or Debian 10+) **/

apt-get update
apt-get upgrade
apt-get install git cmake build-essential libasio-dev libboost-iostreams-dev libboost-locale-dev libboost-system-dev libluajit-5.1-dev libmariadb-dev-compat libpugixml-dev libssl-dev libfmt-dev

cd /directory
mkdir build
cd build
cmake ..
make



/** FOR MACOS **/

// need git
// need cmake
// need pkg-config
// need build-essential

git clone https://github.com/microsoft/vcpkg.git "$HOME/vcpkg"
cd "$HOME/vcpkg"
./bootstrap-vcpkg.sh
./vcpkg integrate install
export VCPKG_ROOT="$HOME/vcpkg"

cd /directory
cmake --preset vcpkg
cmake --build --preset vcpkg --config RelWithDebInfo