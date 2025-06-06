#ifndef _WATLAS_H_
#define _WATLAS_H_

#include <stdlib.h>
#include <optional>
#include <emscripten/bind.h>

#include "../source/xatlas/xatlas.h"

namespace watlas {

struct MeshDecl {
  emscripten::val vertexPositionData;
  std::optional<emscripten::val> vertexNormalData;
  std::optional<emscripten::val> vertexUvData;
  std::optional<emscripten::val> indexData;

  std::optional<emscripten::val> faceMaterialData;
  std::optional<emscripten::val> faceVertexCount;

  uint32_t vertexCount;
  uint32_t vertexPositionStride;
  std::optional<uint32_t> vertexNormalStride;
  std::optional<uint32_t> vertexUvStride;
  std::optional<uint32_t> indexCount;
  std::optional<int32_t> indexOffset;
  std::optional<uint32_t> faceCount;
  std::optional<xatlas::IndexFormat> indexFormat;
  std::optional<float> epsilon;
};

struct UvMeshDecl {
  emscripten::val vertexUvData;
  std::optional<emscripten::val> indexData;
  std::optional<emscripten::val> faceMaterialData;
  uint32_t vertexCount;
  uint32_t vertexStride;
  std::optional<uint32_t> indexCount;
  std::optional<int32_t> indexOffset;
  std::optional<xatlas::IndexFormat> indexFormat;
};

struct ChartOptions {
  std::optional<float> maxChartArea;
  std::optional<float> maxBoundaryLength;

  std::optional<float> normalDeviationWeight;
  std::optional<float> roundnessWeight;
  std::optional<float> straightnessWeight;
  std::optional<float> normalSeamWeight;
  std::optional<float> textureSeamWeight;

  std::optional<float> maxCost;
  std::optional<uint32_t> maxIterations;

  std::optional<bool> useInputMeshUvs;
  std::optional<bool> fixWinding;
};

struct PackOptions {
  std::optional<uint32_t> maxChartSize;
  std::optional<uint32_t> padding;
  std::optional<float> texelsPerUnit;
  std::optional<uint32_t> resolution;
  std::optional<bool> bilinear;
  std::optional<bool> blockAlign;
  std::optional<bool> bruteForce;
  std::optional<bool> rotateChartsToAxis;
  std::optional<bool> rotateCharts;
};

class Atlas {
 public:
  Atlas();
  ~Atlas();

  uint32_t addMesh(MeshDecl meshDecl);
  uint32_t addUvMesh(UvMeshDecl meshDecl);

  void computeCharts(ChartOptions options);
  void packCharts(PackOptions options);
  void generate(ChartOptions chartOptions, PackOptions packOptions);

  // Atlas Results. Only valid after calling generate or compute/packCharts
  emscripten::val getMesh(uint32_t index) const;
  bool getUtilization(const emscripten::val& jsArray) const;
  uint32_t width() const;
  uint32_t height() const;
  uint32_t atlasCount() const;
  uint32_t chartCount() const;
  uint32_t meshCount() const;
  float texelsPerUnit() const;

 private:
  xatlas::Atlas* atlas;
};

}  // namespace watlas

#endif