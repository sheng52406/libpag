/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Tencent is pleased to support the open source community by making libpag available.
//
//  Copyright (C) 2021 THL A29 Limited, a Tencent company. All rights reserved.
//
//  Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file
//  except in compliance with the License. You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  unless required by applicable law or agreed to in writing, software distributed under the
//  license is distributed on an "as is" basis, without warranties or conditions of any kind,
//  either express or implied. see the license for the specific language governing permissions
//  and limitations under the license.
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "EllipseGeometryProcessor.h"
#include "opengl/GLEllipseGeometryProcessor.h"

namespace tgfx {
std::unique_ptr<EllipseGeometryProcessor> EllipseGeometryProcessor::Make(
    int width, int height, bool stroke, bool useScale, const Matrix& localMatrix) {
  return std::unique_ptr<EllipseGeometryProcessor>(
      new EllipseGeometryProcessor(width, height, stroke, useScale, localMatrix));
}

EllipseGeometryProcessor::EllipseGeometryProcessor(int width, int height, bool stroke,
                                                   bool useScale, const Matrix& localMatrix)
    : GeometryProcessor(ClassID()),
      width(width),
      height(height),
      localMatrix(localMatrix),
      stroke(stroke),
      useScale(useScale) {
  inPosition = {"inPosition", ShaderVar::Type::Float2};
  inColor = {"inColor", ShaderVar::Type::Float4};
  if (useScale) {
    inEllipseOffset = {"inEllipseOffset", ShaderVar::Type::Float3};
  } else {
    inEllipseOffset = {"inEllipseOffset", ShaderVar::Type::Float2};
  }
  inEllipseRadii = {"inEllipseRadii", ShaderVar::Type::Float4};
  this->setVertexAttributes(&inPosition, 4);
}

void EllipseGeometryProcessor::onComputeProcessorKey(BytesKey* bytesKey) const {
  uint32_t flags = stroke ? 1 : 0;
  bytesKey->write(flags);
}

std::unique_ptr<GLGeometryProcessor> EllipseGeometryProcessor::createGLInstance() const {
  return std::make_unique<GLEllipseGeometryProcessor>();
}
}  // namespace tgfx
