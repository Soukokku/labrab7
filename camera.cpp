#include <windows.h>
#include <gl/gl.h>
#include "camera.h"
#include <iostream>
#include <math.h>

struct SCamera camera ={-3,-3,3, 400, 500};

void Camera_Poc() {
    glRotatef(-camera.Xrot, 1, 0, 0);
    glRotatef(-camera.Zrot, 0, 0, 1);
    glTranslatef(-camera.x, -camera.y, -camera.z);
}

void Camera_Rotation(float xAngle, float zAngle) {
    camera.Zrot += zAngle;
    if (camera.Zrot < 0) camera.Zrot += 360;
    if (camera.Zrot > 360) camera.Zrot -= 360;
    camera.Xrot += xAngle;
    if (camera.Xrot < 0) camera.Xrot = 0;
    if (camera.Xrot < 180) camera.Xrot = 180;
}

void Camera_AutoMoveByMouse(int centerX, int centerY, float speed) {
    POINT cur;
    POINT base = {centerX, centerY};
    GetCursorPos(&cur);
    Camera_Rotation((base.y - cur.y) / 5, (base.x - cur.x) / 5);
    SetCursorPos(base.x, base.y);
}

void Camera_MoveDirectional(int forwardMove, int rightMove, float speed) {
    float ugol = -camera.Zrot / 180 * M_PI;

    if (forwardMove > 0)
        ugol += rightMove > 0 ? M_PI_4 : (rightMove < 0 ? -M_PI_4 : 0);
    if (forwardMove < 0)
        ugol += M_PI + (rightMove > 0 ? -M_PI_4 : (rightMove < 0 ? M_PI_4 : 0));
    if (forwardMove == 0) {
        ugol += rightMove > 0 ? M_PI_2 : -M_PI_2;
        if (rightMove == 0) speed = 0;
    }

    bool coordinatesChanged = false;
    if (speed != 0) {
        float prev_x = camera.x;
        float prev_y = camera.y;
        float prev_z = camera.z;

        camera.x += sin(ugol) * speed;
        camera.y += cos(ugol) * speed;

        if (camera.x != prev_x || camera.y != prev_y || camera.z != prev_z) {
            coordinatesChanged = true;
        }
    }
}
