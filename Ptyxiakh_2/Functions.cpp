//#include "Functions.h"
//
//#include <iostream>
//
//#include <thread>
//#include <mutex>
//#include <chrono>
//
//static std::mutex for_cout;
//
//void infinite();
//
//void simulation_event_generator()
//{
//    /*std::thread t1*/(infinite);
//
//    /*t1.join();*/
//}
//
//void infinite()
//{
//    bool flag = false;
//
//    while (!flag)
//    {
//        std::lock_guard<std::mutex> block(for_cout);
//        std::cout << "Enter 'e' to exit.\n";
//        char c;
//        std::cin >> c;
//        if (c == 'e')
//        {
//            flag = true;
//        }
//        using namespace std::literals;
//        std::this_thread::sleep_for(200ms);
//    }
//}