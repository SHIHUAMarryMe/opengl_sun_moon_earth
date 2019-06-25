#ifndef __VERTEX_CREATOR_H__
#define __VERTEX_CREATOR_H__


#include <cmath>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class VertexCreator final
{
public:
	VertexCreator() = default;
	VertexCreator(const VertexCreator&) = delete;
	VertexCreator& operator=(const VertexCreator&) = delete;

	// meridianN: the number of meridian
	// line of latitude: the number of latitude.
	// radius: the radius of sphere.
	static inline const std::vector<float>& getSephereVertexPos(const std::size_t& meridianN, const std::size_t& lineOfLatitudeN, const float& radius)noexcept
	{
		VertexCreator::produce_sephere_vertex_data(meridianN, lineOfLatitudeN, radius);
		return VertexCreator::vertex_data_;
	}

private:

	// for sphere.
	static void produce_sephere_vertex_data(const std::size_t& meridianN, const std::size_t& lineOfLatitudeN, const float& radius)noexcept;


	static std::vector<float> vertex_data_;
};



#endif //__VERTEX_CREATOR_H__