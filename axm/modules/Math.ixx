module;

#include "../math.hh"

export module Math;

export namespace axm
{
  using axm::closeEnough;
  using axm::degToRad;
  using axm::radToDeg;
  using axm::dist;
  using axm::distSqr;
  using axm::sign;
  using axm::dot;
  using axm::mag;
  using axm::normalize;
  using axm::cross;
  using axm::sqrt;
  using axm::pow;
  using axm::floor;
  using axm::ceil;
  using axm::round;
  using axm::invert;
  using axm::rotateVec3;
  using axm::conjugate;
  using axm::toEulerRotation;
  using axm::toAxial;
  using axm::matToQuat;
  using axm::rotationFromMouseMovement;
  using axm::fromEulerRotation;
  using axm::fromAxialRotation;
  using axm::lookAtRH;
  using axm::lookAtLH;
  using axm::lookAtSLERP;
  using axm::limitRotationRange;
  using axm::deltaRotationBetweenVectors;
  using axm::correctOrientation;
  using axm::transpose;
  using axm::mat3x3ToMat4x4;
  using axm::mat4x4ToMat3x3;
  using axm::quatToMat3x3;
  using axm::quatToMat4x4;
  using axm::determinant;
  using axm::translateMat;
  using axm::rotateMat;
  using axm::scaleMat;
  using axm::modelMatrix;
  using axm::viewMatrix;
  using axm::perspectiveProjectionMatrix;
  using axm::orthoProjectionMatrix;
  using axm::modelViewProjectionMatrix;
}
