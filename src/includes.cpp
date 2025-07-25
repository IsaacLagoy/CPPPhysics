#include "includes.h"
#include <random>

// random
float uniform(float min, float max) {
    static std::mt19937 rng(std::random_device{}());  // Seed the random engine once
    std::uniform_real_distribution<float> dist(min, max);
    return dist(rng);
}

float uniform() {
    static std::mt19937 rng(std::random_device{}());  // Seed the random engine once
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    return dist(rng);
}


// printing
void print(std::string str) {
    std::cout << str << std::endl;
}

void print(char* str) {
    std::cout << str << std::endl;
}

void print(int n) {
    std::cout << n << std::endl;
}

void print(float f) {
    std::cout << f << std::endl;
}

void print(const vec3& vec) {
    std::cout << "<" << vec.x << ", " << vec.y << ", " << vec.z << ">" << std::endl;
}

// vec6
float dot(vec6 v1, vec6 v2) {
    return glm::dot(v1.linear, v2.linear) + glm::dot(v1.angular, v2.angular);
}

// rotation mapping
vec3 logMapSO3(quat q) {
    if (q.w < 0) q = -q; // find shortest path rotation

    float angle = 2.0f * acos(glm::clamp(q.w, -1.0f, 1.0f));
    float sinHalfAngle = sqrt(1.0f - q.w * q.w);

    if (sinHalfAngle < 1e-7f) return vec3(0); // no rotation

    vec3 axis = glm::normalize(vec3(q.x, q.y, q.z));
    return axis * angle;
}

quat expMapSO3(vec3 omega) {
    float angle = glm::length(omega);
    if (angle < 1e-7f) return quat(); // no rotation

    vec3 axis = omega / angle;
    float halfAngle = 0.5f * angle;
    return quat(cos(halfAngle), axis * sin(halfAngle));
}