#include "Transform.h"

Transform::Transform() { }

Transform::~Transform() { }

void Transform::Update() { }

void Transform::Translate(Vector3f vector) { }

void Transform::Translate(float x, float y, float z) { }

void Transform::Scale(float factor) { }

void Transform::Scale(float h, float w, float d) { }

void Transform::Rotate(float angle, Vector3f axis) { }

void Transform::Rotate(float angle, float x, float y, float z) { }

float* Transform::GetModelToClipMatrix() { 	return nullptr; }
