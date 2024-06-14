#include "Wave.hpp"
#include "Config/ConfigWave.hpp"
#include "Map.hpp"

#include "GLHelpers.hpp"

Wave::Wave()
{
    m_time = 0;
    id_wave = 0;
    ItdWave.read_itd_wave("data/itd_waves.itd");
    Waves = ItdWave.Waves;
    spawnDelay = 3;
    m_lastSpawnTime = 0;
    currentMonsterIndex = 0;
}

void Wave::update(Map map)
{
    for (size_t i = 0; i < currentMonsterIndex; i++)
    {
        Waves[id_wave][i].update();
    }

    const double currentTime{glfwGetTime()};
    // Log::Debug("currentTme : " + std::to_string(currentTime));

    if ((currentTime - m_lastSpawnTime >= spawnDelay) || (currentMonsterIndex == 0))
    {
        if (currentMonsterIndex < Waves[id_wave].size())
        {
            Waves[id_wave][currentMonsterIndex].initTarget(map, textures);
            m_lastSpawnTime = currentTime;
            currentMonsterIndex++;
        }
    }
}

int Wave::get_number_of_target_arrived()
{
    int init_lifes = 0;
    for (size_t i = 0; i < currentMonsterIndex; i++)
    {
        if (Waves[id_wave][i].m_isArrived)
        {
            init_lifes++;
        }
    }
    return init_lifes;
}

void Wave::load(Map map, std::unordered_map<std::string, GLuint> textures)
{
    for (size_t i = 0; i < currentMonsterIndex; i++)
    {
        // Log::Debug("Monster n°" + std::to_string(i) + " is arrived ? " + std::to_string(Waves[id_wave][i].m_isArrived));
        if (!Waves[id_wave][i].m_isArrived || Waves[id_wave][i].m_PointsVie > 0)
        {
            Waves[id_wave][i].move(map, textures);
        }
    }
}