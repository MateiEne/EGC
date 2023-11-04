#pragma once

#include "lab_m1/tema1/game_components/game_scene.h"
#include "core/window/input_controller.h"


namespace m1
{
    class GameSceneInput : public InputController
    {
     public:
        explicit GameSceneInput(GameScene *scene);
        void OnKeyPress(int key, int mods) override;

     public:
        GameScene *scene;
    };
}
