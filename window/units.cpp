#include "units.h"

Units::Info::Info(Models& models, std::string name) {
	model = models.get_info(name);
}

void Units::Info::move(DirectX::XMVECTOR angel, float time_delta) {
	auto normalized_angel = DirectX::XMVector3Normalize(angel);
	auto vector = DirectX::XMVectorScale(angel, time_delta);
	position = DirectX::XMVectorAdd(position, vector);
}

void Units::add_unit(std::string name) {
	std::shared_ptr<Units::Info> unit = std::make_shared<Units::Info>(models, name);
	units.push_back(unit);
}
