echo "[+] Start"

pwd 

echo "[+] Building deps"
mkdir ~/build_dependencies

cd ~/build_dependencies
echo "[+] clone SDL2"
git clone https://github.com/libsdl-org/SDL.git
cd SDL/
cd build
cmake ..
make 
make install 


cd ~/build_dependencies
echo "[+] clone openal-soft"
git clone https://github.com/kcat/openal-soft.git
cd openal-soft/
cd build/
cmake ..
make 
make install

cd ~/build_dependencies
echo "[+] clone zlib"
git clone https://github.com/madler/zlib.git
cd zlib/
./configure 
make 
make install 
echo "[+] Clean up"

