#ifndef __SHADER_CREATOR_H__
#define __SHADER_CREATOR_H__


#include <array>
#include <string>


class ShaderCreator final
{
public:
	ShaderCreator() = default;

	//ShaderCreator(const ShaderCreator& other);
	//ShaderCreator& operator=(const ShaderCretor&);


	void createShadersAndLink(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

private:
	std::string vertex_shader_source_;
	std::string fragment_shader_source_;
};




#endif //__SHADER_CREATOR_H__
