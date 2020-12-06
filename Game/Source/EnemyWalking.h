#include "Entity.h"
#include "DynArray.h"

class EnemyWalking : public Entity
{
public:
	EnemyWalking(int x, int y);

	void Update(float dt) override;

	void SetVelDirection(DirectionState dir);

private:

	int spawnDelay = 0;

	// The original spawning position. The wave will be calculated from that
	int spawnY = 0;

	// The enemy animation
	Animation animLeft;
	Animation animRight;
	Animation deathAnim;

	bool goingRight = false;
	bool goingLeft = false;

	//Pathfinding
	bool hasPath = false;
	DynArray<iPoint> path;

};