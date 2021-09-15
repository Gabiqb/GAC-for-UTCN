//
//  main.cpp
//  Lab3
//
//  Copyright © 2016 CGIS. All rights reserved.
//

#include <iostream>

#include "testTransform.h"
#include "mat3.h"
#include "transform.h"
int main(int argc, const char * argv[]) {
    int nrOfErrors = 0;
    
    nrOfErrors += egc::test2DTransformImplementation();
    nrOfErrors += egc::test3DTransformImplementation();
    egc::vec3 c = egc::vec3(1, 5,1);
    egc::mat3 t = egc::translate(1, 5);
    egc::mat3 t1 = egc::translate(-1, -5);
     egc::mat3 s = egc::scale(3, 3);
     c =   t *s * t1 * c  ;
     std::cout << c.x << " " << c.y<<std::endl;
    std::cout << "Number of errors: " << nrOfErrors << std::endl;
    
    std:getchar();
    
    return 0;
}
