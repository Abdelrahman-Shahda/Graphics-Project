#include <glm/glm.hpp>
struct gameSettings
{
float gameSensitivity;
glm::vec3 velocity;
float friction;
float gravity;
int groundLevel;
int ceilLevel;
int rightBound;
int leftBound;
int cameraConstraintFactor;
bool cameraZoom;
bool cameraPan;
};