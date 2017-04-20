#include "Game.hpp"

//
#include <iostream>
#include <algorithm>

//
#include "Configuration.hpp"
#include "InputManager.hpp"
#include "Asteroid.hpp"

namespace Asteroids
{
	int asteroid_score_value = 100;
	int enemy_score_value = 250;

	Game::Game(int width, int height)
		: m_scene(nullptr)
		, m_width(width)
		, m_height(height)
		, m_player(nullptr)
	{}

	Game::~Game()
	{
		// Destroy the scene
		//
		delete m_scene;

		// Clear list
		//
		m_bullets.clear();

		m_ebullets.clear();
	}

	void Game::Init()
	{
		// Create the scene
		//
		m_scene = new Entities::Scene(
			Engine::Math::Vector3(0.1f, 0.1f, 0.15f),
			m_width,
			m_height
		);

		// Adding the player (ship)
		//
		CreatePlayer();

		// Adding the enemies (asteroids)
		//
		CreateAsteroids(10, Entities::Asteroid::AsteroidSize::BIG);

		//Adding enemy (ship)
		CreateEnemy();
	}

	void Game::Update(double deltaTime)
	{
		// Handle Input
		//
		HandleInput();

		// Update the scene
		//
		m_scene->Update(deltaTime);


		// Look for collisions
		//
		CheckCollisions();


		// Clean up dead bullets
		//
		CleanDeadUpBullets();

		CleanDeadUpEnemyBullets();


		//Enemy control
		//Enemy Respawn
		if (m_enemy->isDestroyed()) EnemyRespawn();

		//Enemy shooting control
		if (!m_enemy->isDestroyed())
		{
			if (m_ShootIntCounter > m_ShootInterval)
			{
				enemyShoot();

				m_ShootIntCounter = 0;

			}

			m_ShootIntCounter = m_ShootIntCounter + 0.1;
		}


		//Check for game over
		if (gameOver())
		{
			//Ship destroyed permanently
			m_player->~Ship();
			std::cout << "Score: " << score << std::endl;

		}
	}

	void Game::Render() const
	{

		//Entity::Render(GL_LINE_LOOP, m_ships[m_currentIndex], m_currentColor);

		// Render the game
		//
		m_scene->Render();

	}

	void Game::HandleInput()
	{
		if (Engine::Input::InputManager::Instance().IsKeyPressed('w'))
		{
			m_player->MoveUp();
		}

		if (Engine::Input::InputManager::Instance().IsKeyPressed('a'))
		{
			m_player->MoveLeft();
		}

		if (Engine::Input::InputManager::Instance().IsKeyPressed('d'))
		{
			m_player->MoveRight();
		}

		if (Engine::Input::InputManager::Instance().IsKeyReleased('p'))
		{
			m_player->ChangeShip();
		}

		if (Engine::Input::InputManager::Instance().IsKeyReleased(' '))
		{
			// If ship is respawning ignore shoot command
			//
			if (m_player->IsRespawning()) return;


			// Shoot!
			//
			Entities::Bullet* pBullet = m_player->Shoot();

			// Store bullets in linked list
			//
			m_bullets.push_back(pBullet);

			// Add bullet to the scene
			//
			m_scene->AddChild(pBullet);
		}
	}

	void Game::CreatePlayer()
	{
		// Loading models
		//
		Utilities::Configuration config;
		m_player = new Entities::Ship(config.LoadModels());

		// Adding the player (ship)
		//		
		m_scene->AddChild(m_player);
	}

	void Game::CreateEnemy()
	{
		Utilities::Configuration config;
		m_enemy = new Entities::Enemy(config.LoadModels());

		// Adding the player (ship)
		//		
		m_scene->AddChild(m_enemy);

	}

	void Game::CreateAsteroids(int amount, Entities::Asteroid::AsteroidSize::Size size, Engine::Math::Vector2 position) const
	{
		for (int i = 0; i < amount; ++i)
		{
			// Create new Asteroid
			Entities::Asteroid* pAsteroid =
				new Entities::Asteroid(size, position);

			// Add asteroid to the scene
			//
			m_scene->AddChild(pAsteroid);

			// If set on origin then move randomly around the 'world'
			if (position == Engine::Math::Vector2::Origin)
			{
				pAsteroid->ApplyRandomTranslation();
			}
		}
	}

	void Game::CreateDebris(Entities::Asteroid* currentAsteroid) const
	{
		// Retrieve current size
		//
		Entities::Asteroid::AsteroidSize::Size currentSize = currentAsteroid->GetSize();

		// Create resulting asteroids from collision depending on current asteroid size
		//
		if (currentSize == Entities::Asteroid::AsteroidSize::BIG)
		{
			CreateAsteroids(2, Entities::Asteroid::AsteroidSize::MEDIUM, currentAsteroid->GetPosition());
		}

		if (currentSize == Entities::Asteroid::AsteroidSize::MEDIUM)
		{
			CreateAsteroids(2, Entities::Asteroid::AsteroidSize::SMALL, currentAsteroid->GetPosition());
		}

		// Remove from scene
		//
		m_scene->RemoveChild(currentAsteroid);
	}

	void Game::CleanDeadUpBullets()
	{
		if (m_bullets.size() == 0) return;

		// Destroy one per update
		//
		auto iter = std::find_if(m_bullets.begin(), m_bullets.end(),
			[&](Entities::Bullet* bullet) { return bullet->ShouldBeDeleted() || bullet->IsColliding(); });
		if (iter != m_bullets.end())
		{
			DestroyBullet(*iter);
		}

	}

	void Game::CleanDeadUpEnemyBullets()
	{
		if (m_ebullets.size() == 0) return;

		//Destroy one enemy bullet per update
		auto iter2 = std::find_if(m_ebullets.begin(), m_ebullets.end(),
			[&](Entities::Bullet* enbullet) { return enbullet->ShouldBeDeleted() || enbullet->IsColliding(); });
		if (iter2 != m_ebullets.end())
		{
			DestroyEnemyBullet(*iter2);
		}
	}



	void Game::CheckCollisions()
	{
		if (!m_player->CanCollide()) return;


		for (auto a : m_scene->GetChildren())
		{
			Entities::Asteroid* pAsteroid = dynamic_cast<Entities::Asteroid*>(a);
			if (pAsteroid)
			{
				CheckCollisionWithPlayer(pAsteroid);
				CheckCollisionWithBullets(pAsteroid);

			}


			CheckCollisionWithEnemyBullets();
		}




	}

	void Game::CheckCollisionWithPlayer(Entities::Asteroid * pAsteroid) const
	{
		if (m_player->IntersectsWith(pAsteroid))
		{
			//Reduce life


			// Create debris
			//
			CreateDebris(pAsteroid);

			//
			m_player->Respawn();
			if (m_player->IsRespawning()) m_player->redLives();

		}

		if (m_player->IntersectsWith(m_enemy))
		{
			m_player->Respawn();
			if (m_player->IsRespawning()) m_player->redLives();
		}

	}

	void Game::CheckCollisionWithBullets(Entities::Asteroid * pAsteroid)
	{
		for (auto bullet : m_bullets)
		{
			if (bullet->IntersectsWith(pAsteroid))
			{
				// Create debris
				//
				CreateDebris(pAsteroid);

				Entities::Asteroid::AsteroidSize::Size currentSize = pAsteroid->GetSize();

				//Calculate point gain based on asteroid size
				// 100 points for destroying BIG asteroids
				if (currentSize == Entities::Asteroid::AsteroidSize::BIG)
				{
					score += asteroid_score_value;
				}
				//Half for MEDIUM
				else if (currentSize == Entities::Asteroid::AsteroidSize::MEDIUM)
				{
					score += (asteroid_score_value / 2);
				}
				//Quarter for SMALL
				else
					score += (asteroid_score_value / 4);

			}

			//Check for bullets collide with enemy, increase score.
			if (bullet->IntersectsWith(m_enemy))
			{
				score += enemy_score_value;

				m_enemy->Destroyed();
				m_enemy->~Enemy();

			}
		}


	}

	void Game::EnemyRespawn()
	{
		if (m_respawnTimeCounter > m_RespawnTime)
		{

			CreateEnemy();
			m_enemy->Respawned();
			m_respawnTimeCounter = 0;

		}
		m_respawnTimeCounter++;
	}

	void Game::CheckCollisionWithEnemyBullets()
	{
		if (!m_player->CanCollide()) return;


		//Iter throught all stored enemy bullets and check for collision
		for (auto bullet2 : m_ebullets)
		{
			if (bullet2->IntersectsWith(m_player))
			{

				//Respawn
				m_player->Respawn();
				if (m_player->IsRespawning()) m_player->redLives();

			}
		}
	}

	void Game::enemyShoot()
	{
		Entities::Bullet* nbullet = m_enemy->Shoot(m_player->GetPosition());

		m_ebullets.push_back(nbullet);

		// Add bullet to the scene

		m_scene->AddChild(nbullet);
	}


	void Game::DestroyBullet(Entities::Bullet * bulletToDestroy)
	{
		// Remove bullet from the scene
		//
		m_scene->RemoveChild(bulletToDestroy);

		// Remove bullet from list
		//
		auto bulletResult = find(m_bullets.begin(), m_bullets.end(), bulletToDestroy);
		if (m_bullets.size() > 0 && bulletResult != m_bullets.end())
		{
			m_bullets.erase(bulletResult);
		}
	}

	void Game::DestroyEnemyBullet(Entities::Bullet * bulletToDestroy)
	{
		// Remove bullet from the scene
		//
		m_scene->RemoveChild(bulletToDestroy);

		// Remove bullet from list
		//
		auto bulletResult = find(m_ebullets.begin(), m_ebullets.end(), bulletToDestroy);
		if (m_ebullets.size() > 0 && bulletResult != m_ebullets.end())
		{
			m_ebullets.erase(bulletResult);
		}
	}


	bool Game::gameOver()
	{
		//Check for lives count
		if (m_player->getLives() == 0) return true;
		else
			return false;


	}


}

