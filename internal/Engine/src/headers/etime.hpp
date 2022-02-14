#pragma once

class ETime {
private:
    static float lastFrame;

public:
    static float deltaTime;
    static void update();
};