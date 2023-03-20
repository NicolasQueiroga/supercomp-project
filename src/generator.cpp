#include <chrono>
#include <random>
#include <fstream>
#include <boost/random.hpp>

void generateInput(int n, int m)
{
    std::ofstream inputFile;
    inputFile.open("../in/input.txt");
    inputFile << n << ' ' << m << '\n';

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);

    // Definindo distribuição normal com média de 3 e desvio padrão de 1
    std::normal_distribution<double> distribution_dif(3, 1.0);

    std::uniform_int_distribution<int> distribution_hr(0, 23);
    std::uniform_int_distribution<int> distribution_cat(1, m);

    std::vector<int> maxFilmes(m); // Vetor para armazenar o máximo de filmes por categoria
    for (int i = 0; i < m; i++)
    {
        maxFilmes[i] = distribution_cat(generator); // Gerando o máximo de filmes para cada categoria
        inputFile << maxFilmes[i] << ' ';           // Escrevendo o valor no arquivo de entrada
    }
    inputFile << '\n';

    for (int i = 0; i < n; i++)
    {
        int hora_inicio = distribution_hr(generator);
        double dif_media = distribution_dif(generator);
        int hora_fim = ((int)hora_inicio + (int)round(dif_media)) % 24;
        int categoria = distribution_cat(generator);

        inputFile << hora_inicio << ' ' << hora_fim << ' ' << categoria << '\n';
    }

    inputFile.close();
}

int main(int argc, char **argv)
{
    generateInput(atoi(argv[1]), atoi(argv[2]));
    return 0;
}