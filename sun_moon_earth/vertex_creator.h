#ifndef __VERTEX_CREATOR_H__
#define __VERTEX_CREATOR_H__


#include <vector>

class VertexCreator final
{
public:
	VertexCreator() = default;
	VertexCreator(const VertexCreator&) = delete;
	VertexCreator& operator=(const VertexCreator&) = delete;

	// meridianN: the number of meridian
	// line of latitude: the number of latitude.
	// radius: the radius of sphere.
	static inline std::vector<float> getSephereVertexPos(const std::size_t& meridianN, const std::size_t& lineOfLatitudeN, const float& radius)noexcept
	{
		auto vertexesData{ VertexCreator::produce_sephere_vertex_data(meridianN, lineOfLatitudeN, radius) };
		return vertexesData;
	}

private:

	// for sphere.
	static std::vector<float> produce_sephere_vertex_data(const std::size_t& meridianN, const std::size_t& lineOfLatitudeN, const float& radius)noexcept;
};



#endif //__VERTEX_CREATOR_H__