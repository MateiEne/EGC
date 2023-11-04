#include "lab_m1/tema1/game_components/game_scene_input.h"

#include <iostream>

using namespace m1;

GameSceneInput::GameSceneInput(GameScene *scene)
{
    this->scene = scene;
}


void GameSceneInput::OnKeyPress(int key, int mods)
{
    if (key == GLFW_KEY_F3)
    {
        scene->ToggleGroundPlane();
    }

    if (key == GLFW_KEY_F5)
    {
        scene->ReloadShaders();
    }

    if (key == GLFW_KEY_ESCAPE)
    {
        scene->Exit();
    }
}
