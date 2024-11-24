#include "game_scene.h"
#include "camera.h"
#include <GL/freeglut.h>

void GameScene::HandleWKeyPress()
{
    camera->MoveForward();
}

void GameScene::HandleAKeyPress()
{
    camera->MoveLeft();
}

void GameScene::HandleSKeyPress()
{
    camera->MoveBackward();
}

void GameScene::HandleDKeyPress()
{
    camera->MoveRight();
}
