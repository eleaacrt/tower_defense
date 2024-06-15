#include "Wave.hpp"
#include "Config/ConfigWave.hpp"
#include "Map.hpp"

#include "GLHelpers.hpp"

Wave::Wave()
{
    m_time = 0;
    ItdWave.read_itd_wave("data/itd_waves.itd");
    Waves = ItdWave.Waves;
    spawnDelay = 5;
    m_lastSpawnTime = 0;
    currentMonsterIndex = 0;
}

void Wave::update(Map map, int &app_current_monster_index, int id_current_wave)
{
    for (size_t i = 0; i < currentMonsterIndex; i++)
    {
        Waves[id_current_wave][i].update();
    }

    const double currentTime{glfwGetTime()};
    // Log::Debug("currentTme : " + std::to_string(currentTime));

    if ((currentTime - m_lastSpawnTime >= spawnDelay) || (currentMonsterIndex == 0))
    {
        if (currentMonsterIndex < Waves[id_current_wave].size())
        {
            Waves[id_current_wave][currentMonsterIndex].initTarget(map, textures);
            m_lastSpawnTime = currentTime;
            currentMonsterIndex++;
            app_current_monster_index = currentMonsterIndex;
        }
    }
}

int Wave::get_number_of_target_arrived(int id_current_wave)
{
    int init_lifes = 0;
    for (size_t i = 0; i < currentMonsterIndex; i++)
    {
        if (Waves[id_current_wave][i].m_isArrived)
        {
            init_lifes++;
        }
    }
    return init_lifes;
}

int Wave::get_number_of_target_dead(int id_current_wave)
{
    int init_dead_targets = 0;
    for (size_t i = 0; i < currentMonsterIndex; i++)
    {
        if (Waves[id_current_wave][i].m_isDead)
        {
            init_dead_targets++;
        }
    }
    return init_dead_targets;
}

void Wave::load(Map map, std::unordered_map<std::string, GLuint> textures, float _viewSize, int &app_current_monster_index, int id_current_wave)
{
    app_current_monster_index = currentMonsterIndex;
    for (size_t i = 0; i < currentMonsterIndex; i++)
    {
        if (!Waves[id_current_wave][i].m_isArrived || Waves[id_current_wave][i].m_PointsVie > 0)
        {
            Waves[id_current_wave][i].move(map, textures, _viewSize);
        }
        // Log::Debug("Monster n°" + std::to_string(i) + " is dead ? " + std::to_string(Waves[id_current_wave][i].m_isDead));
        // Log::Debug("Monster n°" + std::to_string(i) + " is arrived ? " + std::to_string(Waves[id_current_wave][i].m_isArrived));
    }
}