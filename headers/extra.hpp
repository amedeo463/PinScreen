#include <iostream>
#include <bits/stdc++.h>

using namespace std;

void trymkdir(string path__) {
    if (!filesystem::exists(path__)) {
        filesystem::create_directory(path__);
    }  
}

void tryrm(string path__) {
    if (filesystem::exists(path__)) {
        filesystem::remove(path__);
    }
}
