
#include "vertex_creator.h"

#include <array>
#include <cmath>
#include <functional>
#include <iterator>
#include <iostream>

static const float PI{ 3.14159265358979323846f };

// 球面的参数曲线可以用球坐标表示，引入参数u,v，其中v是球面点与原点的连线与z轴正向的夹角，u表示连线在xy平面的投影与x轴正向的夹角
// meridianN: 经线数
// lineOfLatitudeN: 纬线数
std::vector<float> VertexCreator::produce_sephere_vertex_data(const std::size_t &meridianN, const std::size_t &lineOfLatitudeN, const float &radius) noexcept
{
	if (meridianN == 0 || lineOfLatitudeN == 0 || radius == 0)
	{
		return std::vector<float>{};
	}

	std::function<std::array<float, 3>(const float &, const float &)> posInSphere{
		[radius](const float &u, const float &v)->std::array<float, 3> {
			float x{radius * std::sin(PI * v) * std::cos(2.0f * PI * u)};
			float y{radius * std::sin(PI * v) * std::sin(2.0f * PI * u)};
			float z{radius * std::cos(PI * v)};
			return {x, y, z};
		} };

	std::vector<float> vertexesData{};
	std::back_insert_iterator<std::vector<float>> pushBackData(vertexesData);

	float uSpanLength{ 1.0f / meridianN };
	float vSpanLength{ 1.0f / lineOfLatitudeN };

	// 球体最上层是由一个圆来组成的.
	// 该圆又是由三角形组成的
	float u{ 0.0f };
	std::array<float, 3> topCentralPos = posInSphere(.0f, .0f);
	for (std::size_t merIndex = 0; merIndex < static_cast<std::size_t>(meridianN); ++merIndex)
	{
		*(pushBackData++) = topCentralPos[0];
		*(pushBackData++) = topCentralPos[1];
		*(pushBackData++) = topCentralPos[2];

		std::array<float, 3> bottomLeftPos = posInSphere(u, vSpanLength);
		*(pushBackData++) = bottomLeftPos[0];
		*(pushBackData++) = bottomLeftPos[1];
		*(pushBackData++) = bottomLeftPos[2];

		std::array<float, 3> bottomRightPos = posInSphere(u + uSpanLength, vSpanLength);
		*(pushBackData++) = bottomRightPos[0];
		*(pushBackData++) = bottomRightPos[1];
		*(pushBackData++) = bottomRightPos[2];

		u += uSpanLength;
	}

	// 产生中间四边形组顶点数据.
	u = .0f;
	float v{ vSpanLength };

	std::size_t counter{};

	for (std::size_t latitudeIndex = 0; latitudeIndex < lineOfLatitudeN - 1; ++latitudeIndex)
	{
		for (std::size_t meridianIndex = 0; meridianIndex < meridianN; ++meridianIndex)
		{
			std::array<float, 3> topLeftPos = posInSphere(u, v);
			std::array<float, 3> topRightPos = posInSphere(u + uSpanLength, v);

			std::array<float, 3> bottomLeftPos = posInSphere(u, v + vSpanLength);
			std::array<float, 3> bottomRightPos = posInSphere(u + uSpanLength, v + vSpanLength);

			//逆时针绘制.
			//矩形是由两个三角形组成的.
			//逆时针画左上角的三角形.
			*(pushBackData++) = topLeftPos[0];
			*(pushBackData++) = topLeftPos[1];
			*(pushBackData++) = topLeftPos[2];

			*(pushBackData++) = bottomLeftPos[0];
			*(pushBackData++) = bottomLeftPos[1];
			*(pushBackData++) = bottomLeftPos[2];

			*(pushBackData++) = topRightPos[0];
			*(pushBackData++) = topRightPos[1];
			*(pushBackData++) = topRightPos[2];

			//逆时针画矩形右下角的三角形.
			*(pushBackData++) = bottomLeftPos[0];
			*(pushBackData++) = bottomLeftPos[1];
			*(pushBackData++) = bottomLeftPos[2];

			*(pushBackData++) = bottomRightPos[0];
			*(pushBackData++) = bottomRightPos[1];
			*(pushBackData++) = bottomRightPos[2];

			*(pushBackData++) = topRightPos[0];
			*(pushBackData++) = topRightPos[1];
			*(pushBackData++) = topRightPos[2];

			u += uSpanLength;
		}

		u = .0f;
		v += vSpanLength;
	}

	// 球体的最下层也是由一个圆来组成的.
	// 该圆又是由三角形组成的.
	u = .0f;
	std::array<float, 3> bottomCentralPos = posInSphere(0.0, 1.0f);

	for (std::size_t meridianIndex = 0; meridianIndex < static_cast<std::size_t>(meridianN); ++meridianIndex)
	{
		std::array<float, 3> bottomLeftPos = posInSphere(u, 1.0f - vSpanLength);
		std::array<float, 3> bottomRightPos = posInSphere(u + uSpanLength, 1.0f - vSpanLength);

		*(pushBackData++) = bottomCentralPos[0];
		*(pushBackData++) = bottomCentralPos[1];
		*(pushBackData++) = bottomCentralPos[2];

		*(pushBackData++) = bottomLeftPos[0];
		*(pushBackData++) = bottomLeftPos[1];
		*(pushBackData++) = bottomLeftPos[2];

		*(pushBackData++) = bottomRightPos[0];
		*(pushBackData++) = bottomRightPos[1];
		*(pushBackData++) = bottomRightPos[2];
	}

	vertexesData.shrink_to_fit();
	return vertexesData;
}
