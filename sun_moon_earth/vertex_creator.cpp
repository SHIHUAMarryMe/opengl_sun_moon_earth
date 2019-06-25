
#include "vertex_creator.h"


std::vector<float> VertexCreator::vertex_data_{};


void VertexCreator::produce_sephere_vertex_data(const std::size_t & meridianN, const std::size_t & lineOfLatitudeN, const float& radius) noexcept
{
	if (meridianN == 0 || lineOfLatitudeN == 0 || radius == 0)
	{
		return;
	}

	vertex_data_.clear();
	std::size_t vertexN{ meridianN * lineOfLatitudeN + 2 * meridianN };
	vertex_data_.resize(vertexN, .0f);

	for (std::size_t index = 0; index < meridianN; ++index)
	{
		vertex_data_[index * 3] = 0;
		vertex_data_[index * 3 + 1] = 0;
		vertex_data_[index * 3 + 2] = radius;
	}


	float degreesToRadians = 3.141593f / 180.0f; //弧度转换
	float deltaMer = 360.0f / (meridianN - 1);//经度每份对应度数
	float deltaLat = 180.0f / (lineOfLatitudeN + 2);//纬度每份对应度数

	for (int tempLat = 0; tempLat < lineOfLatitudeN; tempLat++)
	{
		float tempAngle1 = ((tempLat + 1)* deltaLat) * degreesToRadians;

		for (int tempMerN = 0; tempMerN < lineOfLatitudeN; tempMerN++)
		{
			float tempAngle2 = (tempMerN*lineOfLatitudeN) * degreesToRadians;
			int tempIndex = tempMerN + tempLat* lineOfLatitudeN + lineOfLatitudeN;

			vertex_data_[tempIndex * 3] = std::sinf(tempAngle1) * std::cosf(tempAngle2)* radius;
			vertex_data_[tempIndex * 3 + 1] = std::sinf(tempAngle1) * std::sinf(tempAngle2)* radius;
			vertex_data_[tempIndex * 3 + 2] = std::cosf(tempAngle1) * radius;
		}
	}

	for (int i = 0; i < meridianN; i++)
	{
		vertex_data_[(vertexN - 1 - i) * 3] = 0;
		vertex_data_[(vertexN - 1 - i) * 3 + 1] = 0;
		vertex_data_[(vertexN - 1 - i) * 3 + 2] = -1.0f * radius;
	}
}
