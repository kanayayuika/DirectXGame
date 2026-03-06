#pragma once
#include "Math.h"
#include <dinput.h>
#include <Windows.h>

class DebugCamera
{
public:
	void Initialize(float clientWidth, float clientHeight);
	void Update(BYTE keys[], BYTE preKeys[], HWND hwnd, int wheelDelta);

	const Matrix4x4& GetViewMatrix() const { return viewMatrix_; }
	const Matrix4x4& GetProjectionMatrix() const { return projectionMatrix_; }

private:
	// 回転
	Vector3 rotation_ = { 0.0f,0.0f,0.0f };
	// 位置
	Vector3 translation_ = { 0.0f,0.0f,-20.0f };
	// ビュー行列
	Matrix4x4 viewMatrix_ = MakeIdentity4x4();
	// 射影行列
	Matrix4x4 projectionMatrix_ = MakeIdentity4x4();

	// マウス
	POINT previousMousePos_{};
	bool isFirstMouse_ = true;
};

