
echo "Starting Compiling.."
# g++ -o functions.o -c functions.cpp

# g++ -g -o functions.o functions.cpp -lstdc++

# gcc -g -o functions.o functions.cpp -lstdc++
# g++ -shared functions.o -o functions.dll

g++ -fPIC -shared -o functions.so functions.cpp


echo "Done compiling.."
echo "Starting Python"
python app.py
