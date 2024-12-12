#include "game_scene.h"
#include "camera.h"
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "game_config.h"

GameScene::GameScene(): Scene{}
{
    camera_ = std::make_unique<Camera>(CAMERA_SPEED);
    model_ = glm::mat4(1.0f);
}

void
GameScene::UpdatePerFrame()
{
    model_ = glm::rotate(model_, GetDeltaTimeMs()/1000.0f * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f)); 
}

void
GameScene::HandleWKeyPress()
{
    camera_->MoveForward();
}

void
GameScene::HandleAKeyPress()
{
    camera_->MoveLeft();
}

void
GameScene::HandleSKeyPress()
{
    camera_->MoveBackward();
}

void 
GameScene::HandleDKeyPress()
{
    camera_->MoveRight();
}
