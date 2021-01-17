#include <glm/glm.hpp>
struct gameSettings
{
float gameSensitivity;
float jumpAmount;
glm::vec3 velocity;
float friction;
float gravity;
int groundLevel;
int planeLevel;
int ceilLevel;
int rightBound;
int leftBound;
int cameraPan;
bool cameraZoom;
bool cameraRotate;
float characterRotation;
glm::vec3 spawnPosition;
};