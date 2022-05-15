#include "camera.hpp"
#include "../ecs/entity.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include "glm/gtx/string_cast.hpp"
#include<iostream>

namespace our {
    // Reads camera parameters from the given json object
    void CameraComponent::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;
        std::string cameraTypeStr = data.value("cameraType", "perspective");
        if(cameraTypeStr == "orthographic"){
            cameraType = CameraType::ORTHOGRAPHIC;
        } else {
            cameraType = CameraType::PERSPECTIVE;
        }
        near = data.value("near", 0.01f);
        far = data.value("far", 100.0f);
        fovY = data.value("fovY", 90.0f) * (glm::pi<float>() / 180);
        orthoHeight = data.value("orthoHeight", 1.0f);
    }

    // Creates and returns the camera view matrix
    glm::mat4 CameraComponent::getViewMatrix() const {
        auto owner = getOwner();
        auto M = owner->getLocalToWorldMatrix();
        //TODO: (Req 7) Complete this function
        //HINT:
        // In the camera space:
        // - eye is the origin (0,0,0)
        glm::vec4 eye = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        // - center is any point on the line of sight. So center can be any point (0,0,z) where z < 0. For simplicity, we let center be (0,0,-1)
        glm::vec4 center = glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);
        // - up is the direction (0,1,0)
        glm::vec4 up = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
        // but to use glm::lookAt, we need eye, center and up in the world state.
        // Since M (see above) transforms from the camera to thw world space, you can use M to compute:
        // - the eye position which is the point (0,0,0) but after being transformed by M
        glm::vec3 Eye = M * eye;
        // - the center position which is the point (0,0,-1) but after being transformed by M
        glm::vec3 Center = M * center;
        
        glm::vec3 Up = M * up;
        return glm::lookAt(Eye, Center, Up);
    }

    // Creates and returns the camera projection matrix
    // "viewportSize" is used to compute the aspect ratio
    glm::mat4 CameraComponent::getProjectionMatrix(glm::ivec2 viewportSize) const {
        //TODO: (Req 7) Wrtie this function
        // NOTE: The function glm::ortho can be used to create the orthographic projection matrix
        // It takes left, right, bottom, top. Bottom is -orthoHeight/2 and Top is orthoHeight/2.
        // Left and Right are the same but after being multiplied by the aspect ratio
        // For the perspective camera, you can use glm::perspective
        if(this->cameraType == CameraType::ORTHOGRAPHIC){
            float top = orthoHeight/2;
            float bot = -orthoHeight/2;
            float right = top  * (viewportSize.x/viewportSize.y);
            float left = -right;//bot  * (viewportSize.x/viewportSize.y);
            return(glm::ortho(left, right, bot, top));
            

        } 
        else if(this->cameraType == CameraType::PERSPECTIVE){
            float aspect = viewportSize.x / viewportSize.y;
          return (glm::perspective(this->fovY, aspect, this->near, this->far));
          
        } else {
            return  glm::mat4(1.0f);
        }

       
    }
}