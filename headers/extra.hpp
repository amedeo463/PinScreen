#include <iostream>
#include <bits/stdc++.h>

using namespace std;

void trymkdir(string path__) {
    // Creates a directory if it does not exist
    if (!filesystem::exists(path__)) {
        filesystem::create_directory(path__);
    }  
}

void tryrm(string path__) {
    // removes an empty diretory if it exists
    if (filesystem::exists(path__)) {
        filesystem::remove(path__);
    }
}
