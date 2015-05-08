#ifndef EXTERNALS_H_
#define EXTERNALS_H_

#include <vector>
#include <memory>

class Dispatcher;
class Core;

extern std::vector<std::unique_ptr<Dispatcher>> vDisp;
extern std::vector<std::unique_ptr<Core>> vCore;


#endif // EXTERNALS_H_
