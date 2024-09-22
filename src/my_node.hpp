#pragma once

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/classes/image_texture.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>
#include "itkImage.h"
#include "itkRandomImageSource.h"

using namespace godot;

class MyNode : public Node3D
{
	GDCLASS(MyNode, Node3D);

protected:
	static void _bind_methods();
	Node *get_node_internal(const NodePath &p_path) const;

public:
	MyNode();
	~MyNode();

	void _ready() override;
	void _process(double delta) override;

	void hello_node();

	void generate_random_image();
};
