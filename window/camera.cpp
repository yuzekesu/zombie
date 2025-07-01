#include "camera.h"

void Camera::follow(std::shared_ptr<Unit::Data> unit_data) {
	assert(unit_data == NULL);
	unit_data_following = unit_data;
	is_following = true;
}

void Camera::follow_stop() {
	assert(unit_data_following != NULL);
	transfer_data_to_camera();
	unit_data_following.reset();
	is_following = false;
}

const DirectX::XMVECTOR& Camera::get_position() {
	if (is_following) {
		assert(unit_data_following != NULL);
		return unit_data_following->get_position();
	}
	return position;
}

const DirectX::XMVECTOR& Camera::get_facing() {
	if (is_following) {
		assert(unit_data_following != NULL);
		return unit_data_following->get_facing();
	}
	return facing;
}

const DirectX::XMVECTOR& Camera::get_translation() {
	if (is_following) {
		assert(unit_data_following != NULL);
		return unit_data_following->get_translation();
	}
	return translation;
}

void Camera::transfer_data_to_camera() {
	assert(unit_data_following.get() != nullptr);
	position = unit_data_following->get_position();
	facing = unit_data_following->get_facing();
	translation = unit_data_following->get_translation();
}
