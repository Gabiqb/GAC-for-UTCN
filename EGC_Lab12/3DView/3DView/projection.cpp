//
//  projection.cpp
//  Lab8_TODO
//
//  Copyright © 2016 CGIS. All rights reserved.
//

#include "projection.h"

namespace egc {
    //define the viewport transformation matrix
    //see section 3 from the laboratory work
    mat4 defineViewTransformMatrix(int startX, int startY, int width, int height)
    {
        mat4 viewTransformMatrix;

        viewTransformMatrix.at(0, 0) = width / 2;
        viewTransformMatrix.at(1, 1) = -height / 2;
        viewTransformMatrix.at(0, 3) = width / 2 + startX;
        viewTransformMatrix.at(1, 3) = height / 2 + startY;

        return viewTransformMatrix;
    }

    //define the camera transformation matrix
    //see section 4 from the laboratory work
    mat4 defineCameraMatrix(Camera mc)
    {
        mat4 cameraMatrix;

        vec3 g = mc.cameraTarget - mc.cameraPosition;
        vec3 w = -g.normalize();
        vec3 u = crossProduct(mc.cameraUp, w).normalize();
        vec3 v = crossProduct(w, u);

        cameraMatrix.at(0, 0) = u.x;
        cameraMatrix.at(0, 1) = u.y;
        cameraMatrix.at(0, 2) = u.z;
        cameraMatrix.at(1, 0) = v.x;
        cameraMatrix.at(1, 1) = v.y;
        cameraMatrix.at(1, 2) = v.z;
        cameraMatrix.at(2, 0) = w.x;
        cameraMatrix.at(2, 1) = w.y;
        cameraMatrix.at(2, 2) = w.z;

        mat4 aux;
        aux.at(0, 3) = -mc.cameraPosition.x;
        aux.at(1, 3) = -mc.cameraPosition.y;
        aux.at(2, 3) = -mc.cameraPosition.z;

        cameraMatrix = cameraMatrix * aux;

        return cameraMatrix;
    }

    //define the projection transformation matrix
    //see section 5 from the laboratory work
    mat4 definePerspectiveProjectionMatrix(float fov, float aspect, float zNear, float zFar)
    {
        mat4 perspectiveProjectionMatrix;

        perspectiveProjectionMatrix.at(0, 0) = -1 / (aspect * tan(fov/ 2));
        perspectiveProjectionMatrix.at(1, 1) = -1 / tan(fov / 2);
        perspectiveProjectionMatrix.at(2, 2) = (zFar + zNear) / (zNear - zFar);
        perspectiveProjectionMatrix.at(2, 3) = 2 * zFar * zNear / (zFar - zNear);
        perspectiveProjectionMatrix.at(3, 2) = 1;
        perspectiveProjectionMatrix.at(3, 3) = 0;

        return perspectiveProjectionMatrix;
    }

    //define the perspective divide operation
    //see section 5 from the laboratory work
    void perspectiveDivide(vec4& iv)
    {
        iv.x = iv.x / iv.w;
        iv.y = iv.y / iv.w;
        iv.z = iv.z / iv.w;
        iv.w = 1;
    }

    //check if a point should be clipped
    //see section 9 from the laboratory work
    bool clipPointInHomogeneousCoordinate(const egc::vec4& vertex)
    {
        if (((-abs(vertex.w) <= vertex.x) && (vertex.x <= abs(vertex.w))) && ((-abs(vertex.w) <= vertex.y) && (vertex.y <= abs(vertex.w))) && ((-abs(vertex.w) <= vertex.z) && (vertex.z <=  abs(vertex.w))))
            return false;
        return true;
    }

    //check if a triangle should be clipped
    //clip only those triangles for which all vertices are outside the viewing volume
    bool clipTriangleInHomegeneousCoordinates(const std::vector<egc::vec4>& triangle)
    {
        for (int i = 0; i < 3; i++)
            if (clipPointInHomogeneousCoordinate(triangle.at(i)))
                return true;
        return false;
    }

    //compute the normal vector to a triangle
    //see section 7 from the laboratory work
    egc::vec3 findNormalVectorToTriangle(const std::vector<egc::vec4>& triangle)
    {
        egc::vec3 n;

        return n;
    }

    //compute the coordinates of the triangle's center
    //(we will use this point to display the normal vector)
    egc::vec4 findCenterPointOfTriangle(const std::vector<egc::vec4>& triangle)
    {
        egc::vec4 triangleCenter;

        return triangleCenter;
    }

    //check if the triangle is visible (front facing)
    //see section 8 from the laboratory work
    bool isTriangleVisible(const std::vector<egc::vec4>& triangle, const egc::vec3& normalVector)
    {
        return true;
    }

    //display the normal vector of a triangle
    //see section 7 from the laboratory work
    //use the SDL_RenderDrawLine to draw the normal vector
    void displayNormalVectors(egc::vec3& normalVector, egc::vec4& triangleCenter)
    {

    }
}
