#include <iostream>

#ifndef LOG_CONFIG_H
#define LOG_CONFIG_H

//                                                 желтый
#define SETUP_BASE_COLOR std::cout<<"\033[33m";
//                                                 красный
#define ERROR_COLOR std::cout<<"\033[91m";
//                                                 синий
#define SAD std::cout<<"\033[34m";
//                                                 сборос к обычным настройкам
#define ANCOLORING std::cout<<"\033[0m";


// для сборки с логами 
// g++ main.cpp -DLOGQM -o program 
// Используем #ifdef для проверки: если LOGQM определен, логируем
#ifdef LOGQM
    #define LOG(txt) \
        do { \
            std::cout << "[Log]:: " << txt << std::endl; \
        } while(0)
#else
    // Если LOGQM не определен, макрос LOG превращается в "пустоту"
    #define LOG(txt) do {} while(0)
#endif

//                                                 обработчик ошибок
#define ERROR(txt) \
    do { \
        ERROR_COLOR; \
        std::cout << "ERROR :: " << txt << std::endl; \
        ANCOLORING; \
        std::terminate();\
    } while(0)


#endif // LOG_CONFIG_H
