#include <CameraController.h>
#include <OGL.h>

void CameraController::moveCamera(int key, Camera camera) {
    Vector3f move = Vector3f(0.0f, 0.0f, 0.0f);
    
    switch(key){
        case GLFW_KEY_UP:
            move.z -= 1.0f;
            break;
        
        case GLFW_KEY_DOWN:
            move.z += 1.0f;
            break;
        
        case GLFW_KEY_LEFT:
            move.x -= 1.0f;
            break;
            
        case GLFW_KEY_RIGHT:
            move.x += 1.0f;
            break;
            
     
    }
    
    camera.Move(move);
    
}
