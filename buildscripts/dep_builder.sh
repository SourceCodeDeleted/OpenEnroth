echo "[+] Start building process"

pwd 
ls 

echo "[+] Building deps"


echo "[+] clone SDL2"
git clone https://github.com/libsdl-org/SDL.git
cd SDL/
mkdir build
cd build
cmake ..
make 
#make install 
cd ../../

echo "[+] clone openal-soft"
git clone https://github.com/kcat/openal-soft.git
cd openal-soft/
cd build/
cmake ..
make 
#make install
cd ../../


echo "[+] clone zlib"
git clone https://github.com/madler/zlib.git
cd zlib/
./configure 
make 
#make install 
cd ../
