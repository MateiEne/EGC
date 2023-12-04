#pragma once

class GameCamera3P {
public:

    GameCamera3P(float distanceToTarget, float targetDegrees) {
        projectionMatrix = glm::mat4(1);

        position = glm::vec3(0, 2, 5);
        forward = glm::vec3(0, 0, -1);
        up = glm::vec3(0, 1, 0);
        right = glm::vec3(1, 0, 0);

        this->distanceToTarget = distanceToTarget;
        this->targetAngle = targetDegrees;
    }

    ~GameCamera3P() { }

    void SetPerspective(float fov, float aspectRatio, float zNear, float zFar) {
        projectionMatrix = glm::perspective(RADIANS(fov), aspectRatio, zNear, zFar);
    }

    void LookAtTarget(glm::vec3 targetPosition, glm::vec3 targetDirection, glm::vec3 targetUp) {
        targetDirection = glm::normalize(targetDirection);
        targetUp = glm::normalize(targetUp);

        // place the camera behind the target and above
        float radians = targetAngle * TO_RADIANS;
        float backwardsLength = cos(radians) * distanceToTarget;
        float upLength = sin(radians) * distanceToTarget;


        position = targetPosition + (-targetDirection) * backwardsLength;
        position += targetUp * upLength;


        forward = glm::normalize(targetPosition - position);
        right = glm::cross(forward, targetUp);
        up = glm::cross(right, forward);
    }

    glm::mat4 GetViewMatrix() {
        // Returns the view matrix
        return glm::lookAt(position, position + forward, up);
    }

    glm::mat4 GetProjectionMatrix() {
        return projectionMatrix;
    }

    void SetDistanceToTarget(float distanceToTarget) {
        this->distanceToTarget = distanceToTarget;
    }

    float GetDistanceToTarget() {
        return distanceToTarget;
    }

    void SetTargetAngle(float targetDegree) {
        targetAngle = targetDegree;
    }

    float GetTargetAngle() {
        return targetAngle;
    }

public:
    float distanceToTarget;
    float targetAngle;

    glm::mat4 projectionMatrix;
    glm::vec3 position;
    glm::vec3 forward;
    glm::vec3 right;
    glm::vec3 up;
};