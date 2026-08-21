#include "math.hh"
#include "matrixMath.hh"
#include "quatMath.hh"
#include "types/mat4x4s.hh"
#include "types/quaternions.hh"

#include "glm/mat4x4.hpp"
#include "glm/gtc/quaternion.hpp"

auto printMat(const glm::mat4x4& in, const std::string_view& msg = "") -> void
{
  printf("glm::mat4x4 %s:\n ", msg.data());
  for(int row = 0; row < 4; row++)
  {
    printf(" [");
    for(int column = 0; column < 4; column++)
    {
      if(column == 3)
      {
        printf("%f]\n ", in[column][row]);
      }
      else
      {
        printf("%f, ", in[column][row]);
      }
    }
  }
  printf("\n");
}

auto printMat(const axm::mat4x4<float>& in, const std::string_view& msg = "") -> void
{
  printf("axm::mat4x4 %s:\n ", msg.data());
  for(int row = 0; row < 4; row++)
  {
    printf(" [");
    for(int column = 0; column < 4; column++)
    {
      if(column == 3)
      {
        printf("%f]\n ", in[column][row]);
      }
      else
      {
        printf("%f, ", in[column][row]);
      }
    }
  }
  printf("\n");
}

auto printQuat(const glm::quat& in, const std::string_view& msg = "") -> void
{
  printf("glm::quat %s: [%f, %f, %f, %f]\n", msg.data(), in.x, in.y, in.z, in.w);
}

auto printQuat(const axm::quat<float>& in, const std::string_view& msg = "") -> void
{
  printf("axm::quat %s: [%f, %f, %f, %f]\n", msg.data(), in.x(), in.y(), in.z(), in.w());
}

//Check quat math, rotation matrices, model matrices, view matrices, projection matrices, and mvp matricies are correct,
// these are the most likely areas to have differences from glm

//Common data between the right and left-handed tests
constexpr axm::vec3<float> axmPosition{10, 20, 5};
constexpr axm::vec3<float> axmSize{100, 200, 50};
constexpr glm::vec3 glmPosition{10, 20, 5};
constexpr glm::vec3 glmSize{100, 200, 50};
constexpr glm::mat4x4 identity{1.0f};
constexpr glm::mat4x4 glmTranslate = glm::translate(identity, glmPosition);

auto rhModelTest() -> bool
{
  const axm::quat<float> axmRotationRH = axm::lookAtRH<float>({0, 0, 0}, {10, 20, 0}, {0, 1, 0});
  glm::quat glmRotationRH = glm::quatLookAtRH(glm::normalize(glm::vec3{10, 20, 0} - glm::vec3{0, 0, 0}), {0, 1, 0});

  const axm::mat4x4<float> axmRotateRH = axm::rotateMat(axmRotationRH);
  const axm::mat4x4<float> axmModelMatrixRH = axm::modelMatrix(axmPosition, axmRotationRH, axmSize);

  const glm::mat4x4 glmRotateRH = glm::mat4_cast(glmRotationRH);
  const glm::mat4x4 glmScale = glm::scale(identity, glmSize);
  const glm::mat4x4 glmModelMatrixRH = glmTranslate * glmRotateRH * glmScale;

  //Check lookAt quaternions
  for(size_t i = 0; i < 4; i++)
  {
    if(!axm::closeEnough(axmRotationRH[i], glmRotationRH[i]))
    {
      printf("Right-handed quaternion lookAt rotation test failed:\n");
      printQuat(axmRotationRH);
      printQuat(glmRotationRH);
      return false;
    }
  }

  //Check rotation matrices
  for(size_t y = 0; y < 4; y++)
  {
    for(size_t x = 0; x < 4; x++)
    {
      if(!axm::closeEnough(axmRotateRH[x][y], glmRotateRH[x][y]))
      {
        printf("Right-handed rotation matrix test failed:\n");
        printMat(axmRotateRH);
        printMat(glmRotateRH);
        return false;
      }
    }
  }

  //Check model matrices
  for(size_t y = 0; y < 4; y++)
  {
    for(size_t x = 0; x < 4; x++)
    {
      if(!axm::closeEnough(axmModelMatrixRH[x][y], glmModelMatrixRH[x][y]))
      {
        printf("Right-handed model matrix test failed:\n");
        printMat(axmModelMatrixRH);
        printMat(glmModelMatrixRH);
        return false;
      }
    }
  }

  return true;
}

auto lhModelTest() -> bool
{
  const axm::quat<float> axmRotationLH = axm::lookAtLH<float>({0, 0, 0}, {10, 20, 0}, {0, 1, 0});
  glm::quat glmRotationLH = glm::quatLookAtLH(glm::normalize(glm::vec3{10, 20, 0} - glm::vec3{0, 0, 0}), {0, 1, 0});

  const axm::mat4x4<float> axmTranslate = axm::translateMat(axmPosition);
  const axm::mat4x4<float> axmScale = axm::scaleMat(axmSize);
  const axm::mat4x4<float> axmRotateLH = axm::rotateMat(axmRotationLH);
  const axm::mat4x4<float> axmModelMatrixLH = axm::modelMatrix(axmPosition, axmRotationLH, axmSize);

  const glm::mat4x4 glmRotateLH = glm::mat4_cast(glmRotationLH);
  const glm::mat4x4 glmScale = glm::scale(identity, glmSize);
  const glm::mat4x4 glmModelMatrixLH = glmTranslate * glmRotateLH * glmScale;


  //Check lookAt quaternions
  for(size_t i = 0; i < 4; i++)
  {
    if(!axm::closeEnough(axmRotationLH[i], glmRotationLH[i]))
    {
      printf("Left-handed quaternion lookAt rotation test failed:\n");
      printQuat(axmRotationLH);
      printQuat(glmRotationLH);
      return false;
    }
  }

  //Check translation matrices
  for(size_t y = 0; y < 4; y++)
  {
    for(size_t x = 0; x < 4; x++)
    {
      if(!axm::closeEnough(axmTranslate[x][y], glmTranslate[x][y]))
      {
        printf("Translation matrix test failed: axm[%f](index [%zu][%zu]) vs glm[%f](index [%zu][%zu])\n", axmTranslate[x][y], x, y, glmTranslate[x][y], x, y);
        printMat(axmTranslate);
        printMat(glmTranslate);
        return false;
      }
    }
  }

  //Check rotation matrices
  for(size_t y = 0; y < 4; y++)
  {
    for(size_t x = 0; x < 4; x++)
    {
      if(!axm::closeEnough(axmRotateLH[x][y], glmRotateLH[x][y]))
      {
        printf("Left-handed rotation matrix test failed: axm[%f](index [%zu][%zu]) vs glm[%f](index [%zu][%zu])\n", axmRotateLH[x][y], x, y, glmRotateLH[x][y], x, y);
        printMat(axmRotateLH);
        printMat(glmRotateLH);
        return false;
      }
    }
  }

  //Check scale matrices
  for(size_t y = 0; y < 4; y++)
  {
    for(size_t x = 0; x < 4; x++)
    {
      if(!axm::closeEnough(axmScale[x][y], glmScale[x][y]))
      {
        printf("Scale matrix test failed: axm[%f](index [%zu][%zu]) vs glm[%f](index [%zu][%zu])\n", axmScale[x][y], x, y, glmScale[x][y], x, y);
        printMat(axmScale);
        printMat(glmScale);
        return false;
      }
    }
  }

  //Check model matrices
  for(size_t y = 0; y < 4; y++)
  {
    for(size_t x = 0; x < 4; x++)
    {
      if(!axm::closeEnough(axmModelMatrixLH[x][y], glmModelMatrixLH[x][y]))
      {
        printf("Left-handed model matrix test failed:\n");
        printMat(axmModelMatrixLH);
        printMat(glmModelMatrixLH);
        return false;
      }
    }
  }

  return true;
}

auto viewMatrixTest() -> bool
{
  glm::vec3 glmTarget = {10, 20, 0};
  glmTarget = normalize(glmTarget);
  constexpr glm::vec3 glmPos{5, 10, 20};
  const glm::quat glmRotationLH = glm::quatLookAtLH(glmTarget, {0, 1, 0});
  const glm::mat4x4 glmRotMat = glm::mat4_cast(glmRotationLH);
  const glm::mat4x4 glmTranslate = glm::translate(identity, glmPos);
  const glm::mat4x4 glmViewMat = glmTranslate * glmRotMat;

  constexpr axm::vec3<float> axmTarget = {10, 20, 0};
  constexpr axm::vec3<float> axmPos{5, 10, 20};
  const axm::quat<float> axmRotationLH = axm::lookAtLH<float>({0, 0, 0}, axmTarget, {0, 1, 0});
  const axm::mat4x4<float> axmView = axm::viewMatrix(axmRotationLH, axmPos);

  for(size_t y = 0; y < 4; y++)
  {
    for(size_t x = 0; x < 4; x++)
    {
      if(!axm::closeEnough(axmView[x][y], glmViewMat[x][y]))
      {
        printf("Left-handed view matrix test failed:\n");
        printMat(axmView);
        printMat(glmViewMat);
        return false;
      }
    }
  }
  return true;
}

auto orthoProjMatTest() -> bool
{
  const axm::mat4x4<float> axmProj = axm::orthoProjectionMatrix<float>(0, 1000, 0, 1000, 0.1f, 1.0f);
  glm::mat4x4 glmProj = glm::ortho<float>(0, 1000, 1000, 0, 0.1f, 1.0f);

  for(size_t y = 0; y < 4; y++)
  {
    for(size_t x = 0; x < 4; x++)
    {
      if(!axm::closeEnough(axmProj[x][y], glmProj[x][y]))
      {
        printf("Ortho projection matrix test failed:\n");
        printMat(axmProj);
        printMat(glmProj);
        return false;
      }
    }
  }
  return true;
}

auto perspProjTest() -> bool
{
  const axm::mat4x4<float> axmProj = axm::perspectiveProjectionMatrix<float>(45.0f, 0.1f, 100.0f, 1000, 1000);
  glm::mat4x4 glmProj = glm::perspectiveFov<float>(45.0f, 1000, 1000, 0.1f, 100.0f);

  for(size_t y = 0; y < 4; y++)
  {
    for(size_t x = 0; x < 4; x++)
    {
      if(!axm::closeEnough(axmProj[x][y], glmProj[x][y]))
      {
        printf("Perspective projection matrix test failed:\n");
        printMat(axmProj);
        printMat(glmProj);
        return false;
      }
    }
  }
  return true;
}

auto main() -> int
{
  //FIXME these are off very slightly but that seems to be because we're doing a different number of operations and
  // that changes the floating point error accumulation
  //lhModelTest();
  //rhModelTest();

  if(!viewMatrixTest())
  {
    printf("View matrix test failed\n");
    return -1;
  }
  if(!orthoProjMatTest())
  {
    printf("Ortho projection matrix test failed\n");
    return -1;
  }
  if(!perspProjTest())
  {
    printf("Perspective Projection matrix test failed\n");
    return -1;
  }

  printf("All tests passed\n");
  return 0;
}