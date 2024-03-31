#include "BaseCharacter.h"
#include "raylib.h"
#include "raymath.h"
BaseCharacter::BaseCharacter(/* args */)
{
}
void BaseCharacter::UndoMovement()
{
    _worldPosition = _worldPositionLastFrame;
}
Rectangle BaseCharacter::GetCollisionRectangle()
{
    return Rectangle{
        GetScreenPosition().x,
        GetScreenPosition().y,
        _width * _scale,
        _height * _scale};
}

void BaseCharacter::Tick(float deltaTime)
{
    _worldPositionLastFrame = _worldPosition;

    // update animation frame
    _runningTime += deltaTime;
    if (_runningTime >= _updateTime)
    {
        _frame++;
        _runningTime = 0.0f;
        if (_frame > _maxFrames)
            _frame = 0;
    }

    if (Vector2Length(_velocity) != 0)
    {
        // set mapPos = mapPos + direction
        _worldPosition = Vector2Add(_worldPosition, Vector2Scale(Vector2Normalize(_velocity), _speed));
        _velocity.x < 1.0f ? _rightLeft = -1.0f : _rightLeft = 1.0f;
        _texture = _runTexture;
    }
    else
    {
        _texture = _idleTexture;
    }

    _velocity = {};
    // Draw character
    Rectangle source{_frame * _width, 0.0, _rightLeft * _width, _height};
    Rectangle dest{GetScreenPosition().x, GetScreenPosition().y, _width * _scale, _height * _scale};

    DrawTexturePro(*_texture, source, dest, Vector2{}, 0.0f, WHITE);
}

bool BaseCharacter::GetAlive()
{
    return _alive;
}

void BaseCharacter::SetAlive(bool isAlive)
{
    _alive = isAlive;
}
