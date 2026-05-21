#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

namespace kirsanov
{
    // Сообщения об ошибках
    const std::string INVALID_COMMAND = "<INVALID COMMAND>";
    const std::string USAGE = "Usage: ";
    const std::string ERROR_PREFIX = "Error: ";

    // Команды (для избежания опечаток)
    const std::string CMD_AREA = "AREA";
    const std::string CMD_MAX = "MAX";
    const std::string CMD_MIN = "MIN";
    const std::string CMD_COUNT = "COUNT";
    const std::string CMD_PERMS = "PERMS";
    const std::string CMD_RIGHTSHAPES = "RIGHTSHAPES";

    // Параметры команд
    const std::string PARAM_EVEN = "EVEN";
    const std::string PARAM_ODD = "ODD";
    const std::string PARAM_MEAN = "MEAN";
    const std::string PARAM_AREA = "AREA";
    const std::string PARAM_VERTEXES = "VERTEXES";
}

#endif
