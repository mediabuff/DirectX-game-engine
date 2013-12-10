

#include "pch.h"
#include "HorizontalSliderPlayer.h"

using namespace Windows::System;
using namespace Windows::UI::Core;


HorizontalSliderPlayer::HorizontalSliderPlayer()
{

	TargetPos = float2(-1, -1);
	vel = float2(0, 0);
	accel.y = 1000;
	weapons_level = WeaponsLevel::single;
}
void HorizontalSliderPlayer::Reset(){
	health = 100;
	TargetPos = (-1.f, -1.f);
	_dead = false;
	weapons_level = WeaponsLevel::single;
	keys_down = 0;
}
void HorizontalSliderPlayer::Shoot()
{

	GlobalData* gdata = GlobalHelper::getData();

	AudioManager::AudioEngineInstance.StopSoundEffect(AudioEngine::SoundEvent::Shoot);
	AudioManager::AudioEngineInstance.PlaySoundEffect(AudioEngine::SoundEvent::Shoot);

	FireBall data(false);
	FireBall data2(false);
	FireBall data3(false);

	switch (weapons_level)
	{
	case WeaponsLevel::single:
		 
		data.SetPos(pos);
		data.vel = float2(1000.0f* cos(rot), -1000.0f*sin(rot));
		data.SetScale(float2(1.0f, 1.0f));
		data.SetTexture(GlobalHelper::getData()->m_particle);
		data.setCollisionGeometryForParticle(float2(20, 20)*data.GetScale(), data.GetPos());
		gdata->bullets.push_back(data);
		break;
	case WeaponsLevel::single_medium: 
		data.SetPos(pos);
		data.vel = float2(1000.0f* cos(rot), -1000.0f*sin(rot));
		data.SetScale(float2(2.0f, 2.0f));
		data.SetTexture(GlobalHelper::getData()->m_particle);
		data.setCollisionGeometryForParticle(float2(20, 20)*data.GetScale(), data.GetPos());
		gdata->bullets.push_back(data);
		break;
	case WeaponsLevel::triple: 

		data.SetPos(pos);
		data.vel = float2(1000.0f* cos(rot), -1000.0f*sin(rot));
		data.SetScale(float2(1.0f, 1.0f));
		data.SetTexture(GlobalHelper::getData()->m_particle);
		data.setCollisionGeometryForParticle(float2(20, 20)*data.GetScale(), data.GetPos());
		gdata->bullets.push_back(data);
		 
		data2.SetPos(float2(pos.x - textureSize.Width / 2.f*scale.x, pos.y - textureSize.Height / 2.f*scale.y + 20));
		data2.vel = float2(1000.0f* cos(rot), -1000.0f*sin(rot));
		data2.SetScale(float2(1.0f, 1.0f));
		data2.SetTexture(GlobalHelper::getData()->m_particle);
		data2.setCollisionGeometryForParticle(float2(20, 20)*data.GetScale(),  data2.GetPos());
		gdata->bullets.push_back(data2);


		data3.SetPos(float2(pos.x - textureSize.Width / 2.f*scale.x, pos.y + textureSize.Height / 2.f*scale.y - 20));
		data3.vel = float2(1000.0f* cos(rot), -1000.0f*sin(rot));
		data3.SetScale(float2(1.0f, 1.0f));
		data3.SetTexture(GlobalHelper::getData()->m_particle);
		data3.setCollisionGeometryForParticle(float2(20, 20)*data.GetScale(),  data3.GetPos());
		 
		gdata->bullets.push_back(data3);
		break;
	case WeaponsLevel::triple_medium:

		data.SetPos(pos);
		data.vel = float2(1000.0f* cos(rot), -1000.0f*sin(rot));
		data.SetScale(float2(2.0f, 2.0f));
		data.SetTexture(GlobalHelper::getData()->m_particle);
		data.setCollisionGeometryForParticle(float2(20, 20)*data.GetScale(),  data.GetPos());
	 
		gdata->bullets.push_back(data);

		data2.SetPos(float2(pos.x - textureSize.Width / 2.f*scale.x, pos.y - textureSize.Height / 2.f*scale.y + 20));
		data2.vel = float2(1000.0f* cos(rot), -1000.0f*sin(rot));
		data2.SetScale(float2(2.0f, 2.0f));
		data2.SetTexture(GlobalHelper::getData()->m_particle);
		data2.setCollisionGeometryForParticle(float2(20, 20)*data.GetScale(), data2.GetPos());
		gdata->bullets.push_back(data2);

		 
		data3.SetPos(float2(pos.x - textureSize.Width / 2.f*scale.x, pos.y + textureSize.Height / 2.f*scale.y - 20));
		data3.vel = float2(1000.0f* cos(rot), -1000.0f*sin(rot));
		data3.SetScale(float2(2.0f, 2.0f));
		data3.SetTexture(GlobalHelper::getData()->m_particle);
		data3.setCollisionGeometryForParticle(float2(20, 20)*data.GetScale(),  data3.GetPos());
		gdata->bullets.push_back(data3);

	}
}

void HorizontalSliderPlayer::SetTarget(float2 newTarget){
	TargetPos = newTarget;
}
void HorizontalSliderPlayer::UpgradeWeapons()
{
	if (weapons_level < 4)
		weapons_level = WeaponsLevel((int) weapons_level + 1);
}
void HorizontalSliderPlayer::Update(float timeDelta)
{
	//vel.y = vel.y + accel.y * timeDelta;

	float2 prevPos = pos;
	float  prevRot = rot;
	if (TargetPos.x != -1)
		pos = pos + float2(TargetPos.x - pos.x, TargetPos.y - pos.y) * timeDelta;
	else
		pos = pos + vel * timeDelta;

	KeepInBounds();
	UpdateChildren(timeDelta);
	UpdateCollisionGeometry(prevPos, pos, prevRot - rot);

}
void HorizontalSliderPlayer::KeepInBounds()
{

	if (pos.x > GlobalHelper::getData()->m_windowBounds.Width - textureSize.Width / 2.0f * scale.x)
	{
		pos.x = GlobalHelper::getData()->m_windowBounds.Width - textureSize.Width / 2.0f * scale.x;
		accel.x = 0;
		vel.x = 0;
	}
	if (pos.y > GlobalHelper::getData()->m_windowBounds.Height - textureSize.Height / 2.0f * scale.y)
	{
		pos.y = GlobalHelper::getData()->m_windowBounds.Height - textureSize.Height / 2.0f * scale.y;

		vel.y = 0;
	}
	if (pos.x < textureSize.Width / 2.0f * scale.x)
	{
		pos.x = textureSize.Width / 2.0f * scale.x;
		accel.x = 0;
		vel.x = 0;
	}
	if (pos.y < textureSize.Height / 2.0f * scale.y)
	{
		pos.y = textureSize.Height / 2.0f * scale.y;

		vel.y = 0;
	}
}


void HorizontalSliderPlayer::ProcessKeyDown(Windows::UI::Xaml::Input::KeyRoutedEventArgs^ args){

	if (args->Key == VirtualKey::Right)
	{
		vel.x = 1000;
	}

	if (args->Key == VirtualKey::Left)
	{
		vel.x = -1000;
	}

	if (args->Key == VirtualKey::Up)
	{

		vel.y = -500;
	}
	if (args->Key == VirtualKey::Down)
	{
		vel.y = 500;
	}

	if (!args->KeyStatus.WasKeyDown)
		keys_down += 1;

	TargetPos = float2(-1, -1);
}
void HorizontalSliderPlayer::ProcessKeyUp(Windows::UI::Xaml::Input::KeyRoutedEventArgs^ args){



	keys_down -= 1;
	if (keys_down == 0)
		vel = (0.f, 0.f);

	if (args->Key == VirtualKey::Space)
	{
		Shoot();
	}
}




void HorizontalSliderPlayer::ProcessPointerPressed(Windows::UI::Input::PointerPoint^ pt)
{

	TargetPos = float2(pt->Position.X, pt->Position.Y);



}
void HorizontalSliderPlayer::ProcessPointerReleased(Windows::UI::Input::PointerPoint^ pt)
{


	TargetPos = float2(-1, -1);
	vel.x = 0;
	rotVel = 0;

}
void HorizontalSliderPlayer::ProcessPointerMoved(Windows::UI::Input::PointerPoint^ pt)
{
	TargetPos = float2(pt->Position.X, pt->Position.Y);

}
