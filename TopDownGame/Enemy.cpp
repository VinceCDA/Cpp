#include "Enemy.h"
#include "raymath.h"
Enemy::Enemy(Vector2 position, Texture2D *idleTexture, Texture2D *runTexture)
{
    _idleTexture = idleTexture;
    _runTexture = runTexture;
    _texture = idleTexture;
    _worldPosition = position;
    _width = _texture->width / _maxFrames;
    _height = _texture->height;
    _speed = 3.5f;
}

void Enemy::Tick(float deltaTime)
{
    if (!GetAlive())
    {
        return;
    }

    _velocity = Vector2Subtract(_target->GetScreenPosition(), GetScreenPosition());
    if (Vector2Length(_velocity) < _radius)
        _velocity = {};
    {
        /* code */
    }

    BaseCharacter::Tick(deltaTime);
    if (CheckCollisionRecs(GetCollisionRectangle(), _target->GetCollisionRectangle()))
    {
        _target->TakeDamage(_damagePerSecond * deltaTime);
    }
}

void Enemy::SetTarget(Character *target)
{
    _target = target;
}

Vector2 Enemy::GetScreenPosition()
{
    return Vector2Subtract(_worldPosition, _target->GetWorldPosition());
}
