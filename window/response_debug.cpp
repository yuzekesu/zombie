#include "app.h"
#include <Windows.h>
#include <sstream>
#include "response_debug.h"


void load_response_debug(App& app) {
	using namespace response_debug;
	app.get_window().get_response().learn(VK_ESCAPE, quit_the_program);
	app.get_window().get_response().learn('T', set_black_transparent);
	app.get_window().get_response().learn('Y', set_magenta_transparent);
	app.get_window().get_response().learn('M', print_frame_interval);
	app.get_window().get_response().learn('K', print_approximate_frame_rate);
	app.get_window().get_response().learn('B', set_frame_rate_60);
	app.get_window().get_response().learn('N', set_frame_rate_30);
	app.get_window().get_response().learn('P', popup_message_box);
	app.get_window().get_response().learn(VK_MOUSEWHEEL, popup_message_box);
	app.get_window().get_response().learn('W', camera_move_forward);
	app.get_window().get_response().learn('S', camera_move_backward);
	app.get_window().get_response().learn('A', camera_move_left);
	app.get_window().get_response().learn('D', camera_move_right);
	app.get_window().get_response().learn(VK_DOWN, camera_rotate_pitch_increase);
	app.get_window().get_response().learn(VK_UP, camera_rotate_pitch_decrease);
	app.get_window().get_response().learn(VK_RIGHT, camera_rotate_yaw_increase);
	app.get_window().get_response().learn(VK_LEFT, camera_rotate_yaw_decrease);
	app.get_window().get_response().learn(VK_SPACE, camera_move_up);
	app.get_window().get_response().learn(VK_CONTROL, camera_move_down);
}

void response_debug::quit_the_program(App& app, const UCHAR vKey) {
	PostMessage(app.get_window().get_hWnd(), WM_CLOSE, NULL, NULL);
	app.get_window().get_response().ignore(vKey);
}

void response_debug::print_frame_interval(App& app, const UCHAR vKey) {
	std::wstringstream test;
	test << app.get_time().get_delta() << "\n";
	OutputDebugString(test.str().c_str());
	app.get_window().get_response().ignore(vKey);
}
void response_debug::print_approximate_frame_rate(App& app, const UCHAR vKey)
{
	std::wstringstream test;
	float frame_rate = 1.f / app.get_time().get_delta();
	test << frame_rate << "\n";
	OutputDebugString(test.str().c_str());
	app.get_window().get_response().ignore(vKey);
}
void response_debug::set_magenta_transparent(App& app, const UCHAR vKey) {
	SetLayeredWindowAttributes(app.get_window().get_hWnd(), RGB(255, 0, 255), NULL, LWA_COLORKEY);
	app.get_window().get_response().ignore(vKey);
}
void response_debug::set_black_transparent(App& app, const UCHAR vKey) {
	SetLayeredWindowAttributes(app.get_window().get_hWnd(), RGB(0, 0, 0), NULL, LWA_COLORKEY);
	app.get_window().get_response().ignore(vKey);
}

void response_debug::set_frame_rate_60(App& app, const UCHAR vKey) {
	app.get_frame_rate() = 60.f;
	std::wstringstream test;
	test << "Frame rate: " << app.get_frame_rate() << "\n";
	OutputDebugString(test.str().c_str());
	app.get_window().get_response().ignore(vKey);
}

void response_debug::set_frame_rate_30(App& app, const UCHAR vKey) {
	app.get_frame_rate() = 30.f;
	std::wstringstream test;
	test << "Frame rate: " << app.get_frame_rate() << "\n";
	OutputDebugString(test.str().c_str());
	app.get_window().get_response().ignore(vKey);
}

void response_debug::popup_message_box(App& app, const UCHAR vKey) {
	MessageBoxA(NULL, "RESPONSE_DEBUG", NULL, NULL);
	app.get_window().get_keyboard().reset();
	app.get_window().get_response().reset_ignoration();
	PostMessage(app.get_window().get_hWnd(), WM_KEYUP, vKey, NULL);
}

void response_debug::camera_move_forward(App& app, const UCHAR vKey) {
	using namespace DirectX;
	XMVECTOR position_now = app.get_camera().get_position();
	XMVECTOR facing_now = app.get_camera().get_facing();
	XMMATRIX facing_now_matrix = XMMatrixRotationRollPitchYawFromVector(facing_now);
	auto move_base_vector = XMVector4Transform({ 0.f,0.f,1.f,1.f }, facing_now_matrix);
	float time_delta = app.get_time().get_delta();
	XMVECTOR move_delta_vector = XMVectorScale(move_base_vector, time_delta);
	XMVECTOR new_position = XMVectorAdd(position_now, move_delta_vector);
	app.get_camera().set_position(new_position);
}

void response_debug::camera_move_backward(App& app, const UCHAR vKey) {
	using namespace DirectX;
	XMVECTOR position_now = app.get_camera().get_position();
	XMVECTOR facing_now = app.get_camera().get_facing();
	XMMATRIX facing_now_matrix = XMMatrixRotationRollPitchYawFromVector(facing_now);
	auto move_base_vector = XMVector4Transform({ 0.f,0.f,1.f,1.f }, facing_now_matrix);
	float time_delta = app.get_time().get_delta();
	XMVECTOR move_delta_vector = XMVectorScale(move_base_vector, time_delta);
	XMVECTOR new_position = XMVectorSubtract(position_now, move_delta_vector);
	app.get_camera().set_position(new_position);
}

void response_debug::camera_move_left(App& app, const UCHAR vKey) {
	using namespace DirectX;
	XMVECTOR position_now = app.get_camera().get_position();
	XMVECTOR facing_now = app.get_camera().get_facing();
	XMMATRIX facing_now_matrix = XMMatrixRotationRollPitchYawFromVector(facing_now);
	auto move_base_vector = XMVector4Transform({ -1.f,0.f,0.f,1.f }, facing_now_matrix);
	float time_delta = app.get_time().get_delta();
	XMVECTOR move_delta_vector = XMVectorScale(move_base_vector, time_delta);
	XMVECTOR new_position = XMVectorAdd(position_now, move_delta_vector);
	app.get_camera().set_position(new_position);
}

void response_debug::camera_move_right(App& app, const UCHAR vKey) {
	using namespace DirectX;
	XMVECTOR position_now = app.get_camera().get_position();
	XMVECTOR facing_now = app.get_camera().get_facing();
	XMMATRIX facing_now_matrix = XMMatrixRotationRollPitchYawFromVector(facing_now);
	auto move_base_vector = XMVector4Transform({ 1.f,0.f,0.f,1.f }, facing_now_matrix);
	float time_delta = app.get_time().get_delta();
	XMVECTOR move_delta_vector = XMVectorScale(move_base_vector, time_delta);
	XMVECTOR new_position = XMVectorAdd(position_now, move_delta_vector);
	app.get_camera().set_position(new_position);
}

void response_debug::camera_rotate_yaw_increase(App& app, const UCHAR vKey) {
	float time_delta = app.get_time().get_delta();
	DirectX::XMVECTOR  facing_now (app.get_camera().get_facing());
	facing_now.m128_f32[1] += time_delta;
	app.get_camera().set_facing(facing_now);
}

void response_debug::camera_rotate_yaw_decrease(App& app, const UCHAR vKey) {
	float time_delta = app.get_time().get_delta();
	DirectX::XMVECTOR facing_now (app.get_camera().get_facing());
	facing_now.m128_f32[1] -= time_delta;
	app.get_camera().set_facing(facing_now);
}

void response_debug::camera_rotate_pitch_increase(App& app, const UCHAR vKey) {
	float time_delta = app.get_time().get_delta();
	DirectX::XMVECTOR facing_now(app.get_camera().get_facing());
	facing_now.m128_f32[0] += time_delta;
	app.get_camera().set_facing(facing_now);
}

void response_debug::camera_rotate_pitch_decrease(App& app, const UCHAR vKey) {
	float time_delta = app.get_time().get_delta();
	DirectX::XMVECTOR facing_now(app.get_camera().get_facing());
	facing_now.m128_f32[0] -= time_delta;
	app.get_camera().set_facing(facing_now);
}

void response_debug::camera_move_up(App& app, const UCHAR vKey) {
	using namespace DirectX;
	XMVECTOR position_now = app.get_camera().get_position();
	XMVECTOR move_base_vector{ 0.f,1.f,0.f,1.f };
	float time_delta = app.get_time().get_delta();
	XMVECTOR move_delta_vector = XMVectorScale(move_base_vector, time_delta);
	XMVECTOR new_position = XMVectorAdd(position_now, move_delta_vector);
	app.get_camera().set_position(new_position);
}

void response_debug::camera_move_down(App& app, const UCHAR vKey) {
	using namespace DirectX;
	XMVECTOR position_now = app.get_camera().get_position();
	XMVECTOR move_base_vector{ 0.f,-1.f,0.f,1.f };
	float time_delta = app.get_time().get_delta();
	XMVECTOR move_delta_vector = XMVectorScale(move_base_vector, time_delta);
	XMVECTOR new_position = XMVectorAdd(position_now, move_delta_vector);
	app.get_camera().set_position(new_position);
}

