#include "DebugCamera.h"
#include <wrl.h>
#include <dinput.h>

void DebugCamera::Initialize(float clientWidth, float clientHeight) {
	rotation_ = { 0.0f,0.0f,0.0f };
	translation_ = { 0.0f,0.0f,-50.0f };

	// 射影行列を作る
	projectionMatrix_ = MakePerspectiveFovMatrix(0.45f, clientWidth / clientHeight, 0.1f, 1000.0f);
	isFirstMouse_ = true;
	// 初期ビュー行列更新
	Vector3 negativeTranslate = { -translation_.x,-translation_.y,-translation_.z };
	Matrix4x4 rotateX = MakeRotateXMatrix(-rotation_.x);
	Matrix4x4 rotateY = MakeRotateYMatrix(-rotation_.y);
	Matrix4x4 rotateZ = MakeRotateZMatrix(-rotation_.z);
	Matrix4x4 rotateMatrix = Multiply(rotateX, Multiply(rotateY, rotateZ));
	Matrix4x4 translateMatrix = MakeTranslateMatrix(negativeTranslate);
	viewMatrix_ = Multiply(rotateMatrix, translateMatrix);
}

void DebugCamera::Update(BYTE keys[], BYTE preKeys[], HWND hwnd, int wheelDelta) {
	const float rotateSpeed = 0.005f;
	const float panSpeed = 0.03f;

	POINT mousePos;
	GetCursorPos(&mousePos);
	ScreenToClient(hwnd, &mousePos);

	if (isFirstMouse_) {
		previousMousePos_ = mousePos;
		isFirstMouse_ = false;
	}

	int deltaX = mousePos.x - previousMousePos_.x;
	int deltaY = mousePos.y - previousMousePos_.y;

	//========================
	// 右ドラッグ：回転
	//========================
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
		rotation_.y += deltaX * rotateSpeed;
		rotation_.x += deltaY * rotateSpeed;
	}

	// 上下向きすぎ防止
	if (rotation_.x > 1.5f) {
		rotation_.x = 1.5f;
	}
	if (rotation_.x < -1.5f) {
		rotation_.x = -1.5f;
	}

	//========================
	// カメラ基準の方向ベクトル
	//========================
	float sinY = std::sin(rotation_.y);
	float cosY = std::cos(rotation_.y);

	Vector3 forward = { sinY, 0.0f, cosY };
	Vector3 right = { cosY, 0.0f, -sinY };
	Vector3 up = { 0.0f, 1.0f, 0.0f };

	//========================
	// ホイール：前後移動
	//========================
	const float zoomSpeed = 0.01f;

	translation_.x += forward.x * wheelDelta * zoomSpeed;
	translation_.z += forward.z * wheelDelta * zoomSpeed;

	//========================
	// 中ドラッグ：平行移動
	//========================
	if (GetAsyncKeyState(VK_MBUTTON) & 0x8000) {
		translation_.x -= right.x * deltaX * panSpeed;
		translation_.z -= right.z * deltaX * panSpeed;

		translation_.y += deltaY * panSpeed;
	}

	//========================
	// リセット
	//========================
	if (keys[DIK_R] && !preKeys[DIK_R]) {
		rotation_ = { 0.0f, 0.0f, 0.0f };
		translation_ = { 0.0f, 0.0f, -50.0f };
	}

	previousMousePos_ = mousePos;

	//========================
	// ビュー行列更新
	//========================
	Vector3 negativeTranslate = { -translation_.x, -translation_.y, -translation_.z };

	Matrix4x4 rotateX = MakeRotateXMatrix(-rotation_.x);
	Matrix4x4 rotateY = MakeRotateYMatrix(-rotation_.y);
	Matrix4x4 rotateZ = MakeRotateZMatrix(-rotation_.z);
	Matrix4x4 rotateMatrix = Multiply(rotateX, Multiply(rotateY, rotateZ));

	Matrix4x4 translateMatrix = MakeTranslateMatrix(negativeTranslate);

	viewMatrix_ = Multiply(rotateMatrix, translateMatrix);
}
