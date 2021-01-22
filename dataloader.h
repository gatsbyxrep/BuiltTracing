#ifndef DATALOADER_H
#define DATALOADER_H
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "line.h"
class DataLoader
{
    // Структура для сохранения загруженных данных
    struct LoadedData
    {
        std::vector<std::vector<Point>> barriers;
        Point startPoint;
        Point endPoint;
    };
    // Вспомогательный метод для разбиения строки
    static std::vector<std::string> split(const std::string& str, const std::string& delim)
    {
        std::vector<std::string> tokens;
        size_t prev = 0, pos = 0;
        do
        {
            pos = str.find(delim, prev);
            if (pos == std::string::npos)
                pos = str.length();
            std::string token = str.substr(prev, pos - prev);
            if (!token.empty()) tokens.push_back(token);
                prev = pos + delim.length();
        } while (pos < str.length() && prev < str.length());
        return tokens;
    }
public:
    // Метод для загрузки данных из файла
    static LoadedData loadFromFile(const std::string& filePath)
    {
        // Объект в который будут записаные считанные данные
        LoadedData result;
        std::ifstream file(filePath);
        if(!file.is_open())
            throw std::exception("Invalid file");
        else
        {
            std::string line;
            while(std::getline(file, line))
            {
                if(line == "Points")
                    break;
                result.barriers.push_back(std::vector<Point>());
                auto barrierPoints = split(line, " ");
                for(auto &elem : barrierPoints)
                {
                    auto barrierCords = split(elem, ",");
                    result.barriers.back().push_back(Point(std::stod(barrierCords[0]), std::stod(barrierCords[1])));
                }
            }
            // Чтение координат начальной и конечной точки
            std::getline(file, line);
            auto point = split(line, ",");
            result.startPoint.x = std::stod(point[0]);
            result.startPoint.y = std::stod(point[1]);
            std::getline(file, line);
            point = split(line, ",");
            result.endPoint.x = std::stod(point[0]);
            result.endPoint.y = std::stod(point[1]);
        }
        return result;
    }
};

#endif // DATALOADER_H
