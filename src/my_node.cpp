#include "my_node.hpp"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void MyNode::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("hello_node"), &MyNode::hello_node);
}

MyNode::MyNode()
{
	UtilityFunctions::print("MyNode created!");
}

MyNode::~MyNode()
{
}

// Override built-in methods with your own logic. Make sure to declare them in the header as well!

void MyNode::_ready()
{
}

void MyNode::_process(double delta)
{
}

void MyNode::hello_node()
{
	UtilityFunctions::print("Hello GDExtension Node!");
}

void MyNode::generate_random_image()
{
	// Use ITK to generate a 2D random image and set it as the mesh texture

	// 定义图像类型
	using PixelType = unsigned char;
	constexpr unsigned int Dimension = 2;
	using ImageType = itk::Image<PixelType, Dimension>;

	// 创建随机图像源
	using RandomImageSourceType = itk::RandomImageSource<ImageType>;
	auto randomImageSource = RandomImageSourceType::New();

	// 设置图像大小和像素值范围
	ImageType::SizeType size;
	size.Fill(256);
	randomImageSource->SetSize(size);
	randomImageSource->SetMin(0);
	randomImageSource->SetMax(255);

	// 生成随机图像
	randomImageSource->Update();
	auto randomImage = randomImageSource->GetOutput();

	// 将 ITK 图像转换为 Godot 图像
	Ref<Image> godotImage = Image::create(size[0], size[1], false, Image::FORMAT_L8);
	PixelType *buffer = randomImage->GetBufferPointer();
	PackedByteArray packedArray;
	packedArray.resize(size[0] * size[1]);
	memcpy(packedArray.ptrw(), buffer, size[0] * size[1]);
	godotImage->set_data(size[0], size[1], false, Image::FORMAT_L8, packedArray);

	// 创建图像纹理
	Ref<ImageTexture> texture = ImageTexture::create_from_image(godotImage);

	// 获取当前节点的 MeshInstance3D 子节点
	Node *node = get_node_internal(NodePath("MeshInstance3D"));
	MeshInstance3D *meshInstance = Object::cast_to<MeshInstance3D>(node);
	if (meshInstance)
	{
		// 获取网格的材质
		Ref<StandardMaterial3D> material = meshInstance->get_surface_override_material(0);
		if (material.is_null())
		{
			material.instantiate();
			meshInstance->set_surface_override_material(0, material);
		}

		// 设置纹理
		material->set_texture(StandardMaterial3D::TEXTURE_ALBEDO, texture);
	}
	else
	{
		UtilityFunctions::print("MeshInstance3D not found!");
	}
}
