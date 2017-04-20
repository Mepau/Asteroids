#pragma once

#ifndef _GAME_H_
#define _GAME_H_

#include <list>

#include "Scene.hpp"
#include "Ship.hpp"
#include "Bullet.hpp"
#include "Asteroid.hpp"
#include "Enemy.h"

// OpenGL includes
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

namespace Asteroids
{
	class Game
	{
	public:
		/* =============================================================
		* CTOR
		* ============================================================= */
		Game(int width, int height);
		~Game();

		/* =============================================================
		* PUBLIC FUNCTIONS
		* ============================================================= */
		void Init();
		void Update(double deltaTime);
		void Render() const;
		int getScore() { return score; };
	private:
		/* =============================================================
		* PRIVATE FUNCTIONS
		* ============================================================= */
		void HandleInput();
		void CreatePlayer();
		void CreateAsteroids(int amount, Entities::Asteroid::AsteroidSize::Size size, Engine::Math::Vector2 position = Engine::Math::Vector2::Origin) const;
		void CreateDebris(Entities::Asteroid* currentAsteroid) const;
		void CleanDeadUpBullets();
		void CleanDeadUpEnemyBullets();
		void CheckCollisions();
		void CheckCollisionWithPlayer(Entities::Asteroid* pAsteroid) const;
		void CheckCollisionWithBullets(Entities::Asteroid* pAsteroid);
		void EnemyRespawn();
		void CheckCollisionWithEnemyBullets();
		void CreateEnemy();
		void DestroyBullet(Entities::Bullet* bulletToDestroy);
		void DestroyEnemyBullet(Entities::Bullet * bulletToDestroy);
		void enemyShoot();
		bool gameOver();


		/* =============================================================
		* MEMBERS
		* ============================================================= */
		Entities::Scene* m_scene;
		int m_width;
		int m_height;
		int score = 0;
		Entities::Ship* m_player;
		Entities::Enemy* m_enemy;
		std::list<Entities::Bullet*> m_bullets;
		std::list<Entities::Bullet*> m_ebullets;
		unsigned int m_respawnTimeCounter = 0;
		unsigned int m_RespawnTime = 2000;
		float m_ShootIntCounter = 0;
		float m_ShootInterval = 10;
	};
}

#endif /* _GAME_H_ */