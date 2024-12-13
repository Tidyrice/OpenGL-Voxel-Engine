#include "game_scene.h"
#include "camera.h"
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "game_config.h"
#include <iostream>

GameScene::GameScene(): Scene{}
{
    camera_ = std::make_unique<Camera>(CAMERA_SPEED, CAMERA_SENSITIVITY);
    model_ = glm::mat4(1.0f);
}

void
GameScene::UpdatePerFrame()
{
    model_ = glm::rotate(model_, GetDeltaTimeMs()/1000.0f * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f)); 
}

void
GameScene::HandleNormalKeys(unsigned char key, int x, int y)
{
    switch (key) {
        case 27: //escape key
            exit(0);
            break;
        case 'w':
            camera_->MoveForward();
            break;
        case 'a':
            camera_->MoveLeft();
            break;
        case 's':
            camera_->MoveBackward();
            break;
        case 'd':
            camera_->MoveRight();
            break;
    }
}

void
GameScene::HandleMouseMovement(int x, int y)
{
    camera_->HandleMouseMovement(x, y);
}