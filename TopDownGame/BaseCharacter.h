#include "raylib.h"
#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

class BaseCharacter
{
private:
    bool _alive{true};

protected:
    Texture2D *_idleTexture{};
    Texture2D *_runTexture{};
    Texture2D *_texture{_idleTexture};
    // Vector2 _screenPosition{}; // where to draw character on the screen.
    Vector2 _worldPosition{};
    Vector2 _worldPositionLastFrame{};
    Vector2 _velocity{};
    // 1:Facing right  -1:Facing left
    float _rightLeft{1.0f};
    // animation variable
    float _runningTime{};
    int _frame{};
    const int _maxFrames{6};
    const float _updateTime{1.0f / 12.0f};

    float _width{};
    float _height{};
    float _playerSpeed{4.0};
    float _speed{4.0f};
    float _scale{4.0f};

public:
    BaseCharacter(/* args */);
    BaseCharacter(Texture2D idleTexture, Texture2D runTexture);
    Vector2 GetWorldPosition() { return _worldPosition; }
    void UndoMovement();
    Rectangle GetCollisionRectangle();
    virtual Vector2 GetScreenPosition() = 0;
    virtual void Tick(float deltaTime);
    bool GetAlive();
    void SetAlive(bool isAlive);
};
#endif
