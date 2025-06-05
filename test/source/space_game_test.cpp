#include "angle/degree.hpp"
#include "vector/vector2i.hpp"
#include "chunk/chunk_coordinate.hpp"

auto main() -> int
{
  // Test basic degree functionality
  sms::Degree deg(90.0);
  if (deg.getDegrees() != 90.0) return 1;

  // Test vector functionality
  sms::Vector2i vec(10, 20);
  if (vec.GetX() != 10 || vec.GetY() != 20) return 1;

  // Test chunk coordinate
  sms::ChunkCoordinate coord;
  if (coord.getChunkX() != 0 || coord.getChunkY() != 0) return 1;

  return 0;
}
