#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"
class Enemy : public BaseCharacter
{
private:
    Character *_target;
    float _damagePerSecond{10.0f};
    float _radius{25.0f};

public:
    Enemy(Vector2 position, Texture2D *idleTexture, Texture2D *runTexture);
    virtual void Tick(float deltaTime) override;
    void SetTarget(Character *target);
    virtual Vector2 GetScreenPosition() override;
};