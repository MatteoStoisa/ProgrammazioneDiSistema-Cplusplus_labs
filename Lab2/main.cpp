
// PDS Lab2
// File System di directory e file

#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "Base.h"
#include "Directory.h"
#include "File.h"

int main() {
    std::cout << "--- Lab2 ---\n" << std::endl;

    std :: shared_ptr < Directory > root = Directory ::getRoot();
    auto alfa = root -> addDirectory( "alfa" );
    alfa -> addDirectory( "beta" )->addFile( "beta1" , 100 );
    alfa -> getDir( "beta" ) -> addFile( "beta2" , 200 );
    alfa -> getDir( ".." ) -> ls();
    alfa -> remove( "beta" );
    root -> ls();

    return 0;
}