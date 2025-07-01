#include "unit.h"

Unit::Data::Data(Mesh& mesh, std::string name) {
	mesh_data = mesh.get_data(name);
	this->name = name;
}

const DirectX::XMVECTOR& Unit::Data::get_position() {
	return position;
}

const DirectX::XMVECTOR& Unit::Data::get_facing() {
	return facing;
}

const DirectX::XMVECTOR& Unit::Data::get_translation() {
	return translation;
}

std::shared_ptr<Mesh::Data> Unit::Data::get_mesh_data()
{
	return mesh_data;
}

void Unit::Data::move(DirectX::XMVECTOR angel, float time_delta) {
	auto normalized_angel = DirectX::XMVector3Normalize(angel);
	auto vector = DirectX::XMVectorScale(angel, time_delta);
	position = DirectX::XMVectorAdd(position, vector);
}

void Unit::add_unit_data(std::string name) {
	std::shared_ptr<Unit::Data> unit = std::make_shared<Unit::Data>(mesh, name);
	units.push_back(unit);
}
