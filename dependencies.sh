sudo apt install git make cmake g++
if [ ! -d "$DIRECTORY" ]; then
    git -c http.sslVerify=false clone --branch master https://github.com/momalab/e3
	cd e3
	git reset --hard f76d1f1fd36bc99783444ab2c1fe1a21c1c09de4
    cd ..
fi
cd e3/3p
make SEAL
