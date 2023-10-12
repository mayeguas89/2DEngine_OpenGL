#include "sprite.h"

#include "common/engine.h"
#include "glad/gl.h"
#include "spdlog/spdlog.h"

#include <array>

Sprite2D::Sprite2D(): Entity()
{
  texture_ = Engine::Instance().GetTexture("Assets/Characters/red/char_red_1.png");
  program_.AddShader("Assets/shaders/sprite.vertex", ShaderType::Vertex);
  program_.AddShader("Assets/shaders/sprite.fragment", ShaderType::Fragment);
  if (!program_.Link())
    spdlog::error("Error in shaders!");

  // configure VAO/VBO
  std::array<glm::vec4, 4> vertexPosition{glm::vec4{-0.5f, -0.5f, 0.f, 0.f},
                                          glm::vec4{-0.5f, 0.5f, 0.f, 0.f},
                                          glm::vec4{0.5f, 0.5f, 0.f, 0.f},
                                          glm::vec4{0.5f, -0.5f, 0.f, 0.f}};
  std::array<uint32_t, 6> indices{0, 1, 2, 0, 2, 3};

  // To show part of the texture we have to show only the appropiate texCoordinates
  // Example: character made of 56x56 px
  // Full texture
  auto texSize = texture_->GetTextureSize();
  const glm::vec<2, int> characterSize{56, 56};
  const glm::vec<2, int> spriteMapSize{6, 11};

  auto x = (1.f / (float)texSize.x) * characterSize.x;
  auto y = (1.f / (float)texSize.y) * characterSize.y;

  const glm::vec<2, int> spriteView{0, 0};

  std::array<glm::vec2, 4> texCoord{glm::vec2{spriteView.x * x, spriteView.y * y},
                                    glm::vec2{spriteView.x * x, spriteView.y * y + y},
                                    glm::vec2{spriteView.x * x + x, spriteView.x * y + y},
                                    glm::vec2{spriteView.x * x + x, spriteView.y * y}};
  // std::array<glm::vec2, 4> texCoord{glm::vec2{0.f, 0.f},
  //                                   glm::vec2{0.f, 1.f},
  //                                   glm::vec2{1.f, 1.f},
  //                                   glm::vec2{1.f, 0.f}};
  glGenVertexArrays(1, &VAO);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPosition), vertexPosition.data(), GL_STATIC_DRAW);

  glGenBuffers(1, &VTO);
  glBindBuffer(GL_ARRAY_BUFFER, VTO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord), texCoord.data(), GL_STATIC_DRAW);

  glGenBuffers(1, &VIO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VIO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);
}

Sprite2D::~Sprite2D() {}

void Sprite2D::Draw()
{
  glBindVertexArray(VAO);
  // Se hace el bind buffer y se suben los datos pertenecientes a este buffer
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // Vertex Position coordinates
  program_.SetVertextAttribArray("vertexPosition", 4, GL_FLOAT, sizeof(glm::vec4), (void*)0x00);

  // Texture coordinates
  glBindBuffer(GL_ARRAY_BUFFER, VTO);
  program_.SetVertextAttribArray("texCoordinate", 2, GL_FLOAT, sizeof(glm::vec2), (void*)0x00);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VIO);

  program_.Use();
  texture_->Bind();
  program_.SetUniformMat4("Model", GetModelMatrix());
  // Set Common stuff like camera matrix
  program_.SetVariables();
  program_.SetUniformMat4("Projection", Engine::Instance().GetMainCamera().GetProjectionMatrix());
  program_.SetUniformMat4("View", Engine::Instance().GetMainCamera().GetViewMatrix());

  glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(6), GL_UNSIGNED_INT, nullptr);
}
